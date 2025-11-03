#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <string>
#include "head.hpp"
using namespace std;

void print_questions_matrix() {
    
  
    vector<string> topics_in_order;
    map<string, bool> topic_seen;


    map<string, vector<int>> topic_costs;


    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 5; col++) {
            auto key = make_pair(row, col);
            auto it = questions_dict.find(key);
            if (it != questions_dict.end()) {
                const Question& question = it->second;
                string topic = question.topic;

                if (!topic_seen[topic]) {
                    topics_in_order.push_back(topic);
                    topic_seen[topic] = true;
                }

                topic_costs[topic].push_back(question.cost);
            }
        }
    }


    if (topics_in_order.size() != 5) {
        topics_in_order.clear();
        topic_seen.clear();


        for (int row = 0; row < 5; row++) {
            for (int col = 0; col < 5; col++) {
                auto key = make_pair(row, col);
                auto it = questions_dict.find(key);
                if (it != questions_dict.end()) {
                    string topic = it->second.topic;
                    if (!topic_seen[topic]) {
                        topics_in_order.push_back(topic);
                        topic_seen[topic] = true;
                        break;
                    }
                }
            }
        }
    }


    const int TOPIC_WIDTH = 30;
    const int COST_WIDTH = 10;
    const int COLS = 5;

    auto print_line = [&]() {
        cout << "|";
        for (int i = 0; i <= COLS; i++) {
            int width = (i == 0) ? TOPIC_WIDTH : COST_WIDTH;
            cout << string(width, '-');
            if (i < COLS) cout << "|";
            else cout << "|";
        }
        cout << endl;
        };

    cout << "+" << string(TOPIC_WIDTH, '-') << "+";
    for (int i = 0; i < COLS; i++) {
        cout << string(COST_WIDTH, '-');
        if (i < COLS - 1) cout << "+";
    }
    cout << "+" << endl;

    for (size_t topic_idx = 0; topic_idx < topics_in_order.size(); topic_idx++) {
        string topic = topics_in_order[topic_idx];

        string topic_display = to_string(topic_idx+1)+ ")" + topic;
        /*if (topic_display.length() > TOPIC_WIDTH - 2) {
            topic_display = topic_display.substr(0, TOPIC_WIDTH - 3) + ".";
        }*/
        
        cout << "| " << left << setw(TOPIC_WIDTH - 1) << (topic_display);

        vector<int> costs = topic_costs[topic];

        for (int col = 0; col < COLS; col++) {
            string cost_display = "";
            if (col < costs.size()) {
                cost_display = to_string(costs[col]);
            }
            else {

                cost_display = "";
            }

            int padding = COST_WIDTH - cost_display.length();
            int left_padding = padding / 2;
            int right_padding = padding - left_padding;

            cout << "|" << string(left_padding, ' ') << cost_display << string(right_padding, ' ');
        }
        cout << "|" << endl;
        
        if (topic_idx < topics_in_order.size() - 1) {
            print_line();
        }
    }

    cout << "+" << string(TOPIC_WIDTH, '-') << "+";
    for (int i = 0; i < COLS; i++) {
        cout << string(COST_WIDTH, '-');
        if (i < COLS - 1) cout << "+";
    }
    cout << "+" << endl;

   /* cout << "\nПорядок тем в матрице: ";
    for (size_t i = 1; i < topics_in_order.size()+1; i++) {
        cout << (i) << ")" << topics_in_order[i-1];
        if (i < topics_in_order.size()-1) cout << ", ";
    }*/
    cout << endl;
}