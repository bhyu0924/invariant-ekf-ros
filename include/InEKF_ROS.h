#ifndef INEKF_ROS_H
#define INEKF_ROS_H 
#include <Eigen/Dense>
#include <memory>
#include <chrono>
#include <thread>
#include <boost/lockfree/queue.hpp>
#include "ros/ros.h"
#include "sensor_msgs/Imu.h"
#include "InEKF.h"
#include "Measurement.h"
#include "Queue.h"

class InEKF_ROS {
    public:
        InEKF_ROS(ros::NodeHandle n);
        void init();
        void run();

    private: 
        ros::NodeHandle n_;
        inekf::InEKF filter_;
        ros::Subscriber imu_sub_;
        std::thread filtering_thread_;
        Queue<std::shared_ptr<Measurement>> m_queue_;
        //std::queue<sensor_msgs::Imu::ConstPtr> imu_queue_;
        //boost::lockfree::queue<Measurement*, boost::lockfree::capacity<200>> m_queue_;

        //std::mutex imu_mutex_;

        void subscribe();
        void mainFilteringThread();
        void imuCallback(const sensor_msgs::Imu::ConstPtr& msg); 
};

#endif 
