#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <thread>
#include <algorithm>
#include <exception>

using namespace std;

constexpr size_t CHUNK_SIZE = 1024 * 1024;

void bin_file_sort()
{
    uint64_t *buf = new uint64_t[CHUNK_SIZE];
    ifstream input("in.txt", ios::binary);
    if (!input) {
    	delete[] buf;
    	throw ifstream::failure("Failed to open in.txt");
    }
    size_t files_cnt = 0;

    vector<string> files_names;
    while (input) {
        input.read(reinterpret_cast<char *>(buf), CHUNK_SIZE * sizeof(uint64_t));
        size_t read_size = input.gcount() / sizeof(uint64_t);
        if (read_size > 0) {
            files_names.push_back(to_string(files_cnt++));
            files_names.push_back(to_string(files_cnt++));

            std::thread t1([buf, read_size]() { 
                sort(buf, buf + (read_size / 2)); 
            });
            std::thread t2([buf, read_size]() {
                sort(buf + read_size / 2 , buf + read_size);
            });
            t1.join();
            t2.join();
            

            std::ofstream f1(files_names[files_cnt - 2], std::ios::binary);
            if (!f1) {
            	delete[] buf;
                throw std::ofstream::failure(files_names[files_cnt - 2]);
            }
            f1.write(reinterpret_cast<const char*>(buf), sizeof(uint64_t) * read_size / 2);

            std::ofstream f2(files_names[files_cnt - 1], std::ios::binary);
            f2.write(reinterpret_cast<const char*>(buf + read_size / 2), sizeof(uint64_t) * read_size / 2);
            if (!f2) {
            	delete[] buf;
                throw std::ofstream::failure(files_names[files_cnt - 1]);
            }
            f1.close();
            f2.close();
        
        }
    }
    input.close();
    delete[] buf;
    ofstream out("out.txt", ios::binary);
    vector <ifstream> tmp_files (files_cnt);

   
    for (size_t i = 0; i < files_cnt; ++i) {
        tmp_files[i] = ifstream(files_names[i], ios::binary | ios::in);
        if (!tmp_files[i]) {
            throw std::ifstream::failure(files_names[i]);
        }
    }
   
    auto comprt = [](const pair<uint64_t, int>& lhs, const pair<uint64_t, int>& rhs) {
        return lhs.first > rhs.first;
    };
    priority_queue<pair<uint64_t, int>,
                   vector<pair<uint64_t, int>>,
                   decltype(comprt)> heap(comprt);

   
    for (size_t i = 0; i < files_cnt; ++i) {
        uint64_t number; // pair(current_number on file i, index of file i)
        tmp_files[i].read(reinterpret_cast<char *>(&number), sizeof(uint64_t));
        heap.emplace(make_pair(number, i));
    }

    while (!heap.empty()) {        
        uint64_t current = heap.top().first;
        size_t file_idx = heap.top().second;

        heap.pop();
        out.write(reinterpret_cast<char *>(&current), sizeof(uint64_t));
        
        if (tmp_files[file_idx].peek() != EOF) {
            uint64_t next;
            tmp_files[file_idx].read(reinterpret_cast<char*>(&next), sizeof(uint64_t));
            heap.emplace(make_pair(next, file_idx));
        }
    }
    for (size_t i = 0; i < files_cnt; ++i) {
        tmp_files[i].close();
        remove(files_names[i].c_str());
    }
    out.close();
}
int main(void)
{
    try {
        bin_file_sort();   
    } 
    catch (std::exception &e) {
        cout << e.what() << endl;
        return 1;
    }
    return 0;
}