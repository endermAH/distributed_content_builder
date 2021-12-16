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

const int kAgentCount = 3;
const int kBuildCount = 15;

class Agent {
    
    class Queue {
    public:
        class Job {
        public:
            int count_;
            Agent* assigned_agent_;
            int status_;
        public:
            Job(int count) {
                count_ = count;
                status_ = JOB_READY_FOR_BUILD;
            }
        };
        
    public:
        enum JobStatus {
            JOB_IN_PROGRESS, JOB_DONE, JOB_READY_FOR_BUILD, JOB_FAILED
        };
        Job* job_list_;
        int job_count_;
        
    public:
        Queue(int count){
            job_count_ = count;
            job_list_ = static_cast<Job*>(malloc(sizeof(Job)*count));
            for(int i = 0; i < count; i++) {
                new(job_list_ + i) Job(1);
            }
        }
        
        Queue(int min, int max, int count){
            std::srand(std::time(nullptr));
            int* jobs_sizes_ = static_cast<int*>(malloc(sizeof(int)*count));
            int tmp_count = count;
            job_count_ = 0;
            int rand_count;
            
            while (tmp_count > max) {
                rand_count = min + std::rand() % (max-min);
                jobs_sizes_[job_count_] = rand_count;
                tmp_count -= rand_count;
                job_count_++;
            }
            jobs_sizes_[job_count_] = tmp_count;
            job_count_++;
            
            job_list_ = static_cast<Job*>(malloc(sizeof(Job)*job_count_));
            for(int i = 0; i < job_count_; i++) {
                new(job_list_ + i) Job(jobs_sizes_[i]);
            }
            
            std::cout << "Jobs to do: \n";
            for (int i=0; i<job_count_; i++){
                std::cout << job_list_[i].count_ << " ";
            }
            std::cout << std::endl;
            
            free(jobs_sizes_);
        }
        
        bool AssignJob(Agent* a){
            Job* job;
            bool job_assigned = false;
            for(int i = 0; i < job_count_; i++) {
                if (job_list_[i].status_ == JOB_READY_FOR_BUILD || job_list_[i].status_ == JOB_FAILED) {
                    job = &job_list_[i];
                    job->assigned_agent_ = a;
                    job->status_ = JOB_IN_PROGRESS;
                    job_assigned = true;
                    a->doJob(job);
                    break;
                }
            }
            return job_assigned;
        }
        
        bool JobsDone() {
            bool done = true;
            for(int i = 0; i < job_count_; i++) {
                if (job_list_[i].status_ != JOB_DONE) {
                    done = false;
                }
            }
            return done;
        }
        
    };

public:
    int state_;
    int identity_;
    enum States {
        STATE_AVAILABLE, STATE_BUSY, STATE_OFFLINE
    };
public:
    Agent(int id) {
        state_ = STATE_AVAILABLE;
        identity_ = id;
    }
    
    void doJob(Queue::Job* job) {
        auto workflow = [](Queue::Job* j, Agent* a){
            a->state_ = STATE_BUSY;
            printf("[%d] Job started (%d)\n", a->identity_, j->count_);
            usleep(1000000 * j->count_);
            printf("[%d] Job finished\n", a->identity_);
            j->status_ = Queue::JOB_DONE;
            a->state_ = STATE_AVAILABLE;
        };
        std::thread thread(workflow, job, this);
        thread.detach();
    }
    
    Agent* getAllAgents() {
        return generateAgents(kAgentCount);
    }
    
    double buildContent(int count) {
        Agent* a_list = getAllAgents();
        Queue* q = new Queue(1, 5, count);
        time_t start, end;
        time(&start);
        while (!q->JobsDone()) {
            for (int i = 0; i < kAgentCount; i++) {
                if(a_list[i].state_ == STATE_AVAILABLE) {
                    q->AssignJob(&a_list[i]);
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
    Agent* generateAgents(int count) {
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
    
    const int tests_cout = 100;
    
    double time[tests_cout];
    double summ = 0;
    for(int i = 0; i < tests_cout; i++) {
        time[i] = current_agent->buildContent(kBuildCount);
        summ += time[i];
    }
    double avg = summ/tests_cout;
    
    std::cout << "Agent count: " << kAgentCount << std::endl;
    std::cout << "Build count: " << kBuildCount << std::endl;
    std::cout << "Average build time: " << avg << std::endl;
    std::cout << "Time for each build: " << std::endl;
    for(int i = 0; i < tests_cout; i++) {
        std::cout << time[i] << " ";
    }
    
    
    return 0;
}
