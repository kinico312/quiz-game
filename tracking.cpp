#include "head.hpp"
#include <mutex>

namespace Tracking {

    namespace {
        // Глобальное хранилище текущего пользователя с защитой от гонок
        User g_current_user{ "", 0 };
        bool g_initialized = false;
        std::mutex g_mutex;
    }

    void init_default_user(const std::string& name)
    {
        std::lock_guard<std::mutex> lock(g_mutex);
        g_current_user.name = name;
        g_current_user.score = 0;
        g_initialized = true;
    }

    void add_score(int points) noexcept
    {
        try {
            std::lock_guard<std::mutex> lock(g_mutex);
            if (!g_initialized) {
                g_current_user.name = "Player";
                g_current_user.score = 0;
                g_initialized = true;
            }
            if (points > 0) {
                g_current_user.score += points;
            }
        } catch (...) {
            // По требованиям устойчивости — гасим ошибки
        }
    }

    const User& current_user() noexcept
    {
        try {
            std::lock_guard<std::mutex> lock(g_mutex);
            if (!g_initialized) {
                g_current_user.name = "Player";
                g_current_user.score = 0;
                g_initialized = true;
            }
            return g_current_user;
        } catch (...) {
            // В крайне маловероятном случае возвратим статический запасной объект
            static User fallback{ "Player", 0 };
            return fallback;
        }
    }
}


