//
//  main.cpp
//  distributed_content_builder
//
//  Created by Евгений Курятов on 16.12.2021.
//

#include <iostream>
#include <unistd.h>
#include <thread>
#include <time.h>
#include <cstdlib>

const int kAgentCount = 10;
const int kBuildSize = 100;
const int kTestsCount = 1;

class Agent {
    
    class Queue {
    public:
        class Task {
        public:
            int size_;
            Agent* assigned_agent_;
            int status_;
        public:
            Task(int count) {
                size_ = count;
                status_ = TASK_READY_FOR_BUILD;
            }
        };
        
    public:
        enum TaskStatus {
            TASK_IN_PROGRESS, TASK_DONE, TASK_READY_FOR_BUILD, TASK_FAILED
        };
        Task* task_list_;
        int task_count_;
        
    public:
        Queue(int count){
            task_count_ = count;
            task_list_ = static_cast<Task*>(malloc(sizeof(Task)*count));
            for(int i = 0; i < count; i++) {
                new(task_list_ + i) Task(1);
            }
        }
        
        Queue(int min, int max, int count){
            std::srand(std::time(nullptr));
            int* task_sizes_ = static_cast<int*>(malloc(sizeof(int)*count));
            int tmp_count = count;
            task_count_ = 0;
            int rand_count;
            
            while (tmp_count > max) {
                rand_count = min + std::rand() % (max-min);
                task_sizes_[task_count_] = rand_count;
                tmp_count -= rand_count;
                task_count_++;
            }
            task_sizes_[task_count_] = tmp_count;
            task_count_++;
            
            task_list_ = static_cast<Task*>(malloc(sizeof(Task)*task_count_));
            for(int i = 0; i < task_count_; i++) {
                new(task_list_ + i) Task(task_sizes_[i]);
            }
            
            std::cout << "Jobs to do: \n";
            for (int i=0; i<task_count_; i++){
                std::cout << task_list_[i].size_ << " ";
            }
            std::cout << std::endl;
            
            free(task_sizes_);
        }
        
        bool AssignTask(Agent* a){
            Task* task;
            bool task_assigned = false;
            for(int i = 0; i < task_count_; i++) {
                if (task_list_[i].status_ == TASK_READY_FOR_BUILD || task_list_[i].status_ == TASK_FAILED) {
                    task = &task_list_[i];
                    task->assigned_agent_ = a;
                    task->status_ = TASK_IN_PROGRESS;
                    task_assigned = true;
                    a->DoTask(task);
                    break;
                }
            }
            return task_assigned;
        }
        
        bool AllTasksComplete() {
            bool done = true;
            for(int i = 0; i < task_count_; i++) {
                if (task_list_[i].status_ != TASK_DONE) {
                    done = false;
                }
            }
            return done;
        }
        
    };

public:
    enum States {
        STATE_AVAILABLE, STATE_BUSY, STATE_OFFLINE
    };
    int state_;
    int identity_;

public:
    Agent(int id) {
        state_ = STATE_AVAILABLE;
        identity_ = id;
    }
    
    void DoTask(Queue::Task* job) {
        auto payload = [](Queue::Task* j, Agent* a){
            a->state_ = STATE_BUSY;
            printf("[%d] Job started (%d)\n", a->identity_, j->size_);
            usleep(1000000 * j->size_);
            printf("[%d] Job finished\n", a->identity_);
            j->status_ = Queue::TASK_DONE;
            a->state_ = STATE_AVAILABLE;
        };
        std::thread thread(payload, job, this);
        thread.detach();
    }
    
    Agent* GetAllAgents() {
        return GenerateAgents(kAgentCount);
    }
    
    double BuildContent(int count) {
        Agent* a_list = GetAllAgents();
        Queue* q = new Queue(1, 10, count);
        time_t start, end;
        time(&start);
        while (!q->AllTasksComplete()) {
            for (int i = 0; i < kAgentCount; i++) {
                if(a_list[i].state_ == STATE_AVAILABLE) {
                    q->AssignTask(&a_list[i]);
                }
            }
            usleep(1000);
        }
        time(&end);
        double build_time = difftime(end, start);
        std::cout << "Build time: " << build_time << "s" << std::endl;
        return build_time;
        
    }
private:
    Agent* GenerateAgents(int count) {
        Agent* agents;
        agents = static_cast<Agent*>(malloc(sizeof(Agent)*count));
        for(int i = 0; i < count; i++){
            new(agents + i) Agent(i);
        }
        return agents;
    }
};

int main(int argc, const char * argv[]) {
    Agent* current_agent = new Agent(999);
    
    double time[kTestsCount];
    double summ = 0;
    for(int i = 0; i < kTestsCount; i++) {
        time[i] = current_agent->BuildContent(kBuildSize);
        summ += time[i];
    }
    double avg = summ/kTestsCount;
    
    std::cout << "Agent count: " << kAgentCount << std::endl;
    std::cout << "Build count: " << kBuildSize << std::endl;
    std::cout << "Average build time: " << avg << std::endl;
    std::cout << "Time for each build: " << std::endl;
    for(int i = 0; i < kTestsCount; i++) {
        std::cout << time[i] << " ";
    }
    
    
    return 0;
}
