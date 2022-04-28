/* ROS interfaces */
#include "ros/ros.h"
#include "sensor_msgs/Imu.h"
#include "sensor_msgs/JointState.h"
#include "geometry_msgs/TwistStamped.h"
#include <vector>

/* Husky Data Structures For Internal Program */
#include "utils/husky_data.hpp"
#include "utils/imu.hpp"
#include "utils/joint_state.hpp"
#include "utils/velocity.hpp"
#include "utils/camera_odom.hpp"

#include <thread>
#include <string>
#include <unsupported/Eigen/MatrixFunctions>

#include <iostream>
#include <fstream>

class HuskyComms {
    public:
        HuskyComms(ros::NodeHandle* nh, husky_inekf::husky_data_t* husky_data_buffer);
        ~HuskyComms();

    private:
        void imuCallback(const sensor_msgs::Imu& imu_msg);
        void jointStateCallback(const sensor_msgs::JointState& joint_msg);
        void jointStateVelocityCallback(const sensor_msgs::JointState& joint_msg);
        void GPSvelocityCallback(const geometry_msgs::TwistStamped& vel_msg);
        void CameraOdomCallBack(const nav_msgs::Odometry& camera_odom_msg);
        // void velocityCallback(const MeasurementType vel_type);
        
        void sub();

        ros::NodeHandle* nh_;
        ros::Subscriber imu_sub_;
        ros::Subscriber joint_sub_;
        ros::Subscriber vel_sub_;
        ros::Subscriber odom_record_sub_;

        std::ofstream outfile_;

        std::thread subscribing_thread_;

        std::vector<double> translation_imu;
        std::vector<double> rotation_imu;
        std::vector<double> rotation_body_imu;

        husky_inekf::husky_data_t* husky_data_buffer_;

};
