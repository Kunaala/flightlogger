
MIT License

Copyright (c) 2020 Kunaal A Malodhakar and  Chetan chadha

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
  
  
#include<ros/ros.h>
#include<ros/console.h>
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/NavSatFix.h>
#include<geometry_msgs/Vector3.h>
#include<fstream>
#include<iostream>
#include<string>
#include<typeinfo>
#include<std_msgs/Float64.h>
#include "boost/date_time/posix_time/posix_time.hpp"
//#include <tf2/LinearMath/Quaternion.h>
#include<tf/tf.h>
std::string homepath=std::getenv("HOME");
std::string path=homepath+"/flightlogs.csv";        //location of flightlogs.csv
void imucb(const sensor_msgs::Imu::ConstPtr& msg)		///callback for /mavros/imu/data subscription
  {
    // boost::posix_time::ptime Ptime = ros::Time::now().toBoost(); //posix string time "conversion of UNIX to POSIX type"
    // std::string curt = boost::posix_time:: to_iso_extended_string(Ptime);
    double roll, pitch, yaw;
    std::ofstream fil;
    fil.open(path, std::fstream::app);

    fil << msg->header.seq;
    tf::Quaternion q(
           msg->orientation.x,
           msg->orientation.y,
           msg->orientation.z,
           msg->orientation.w);
    tf::Matrix3x3 m(q);
    m.getRPY(roll, pitch, yaw);
    fil << "," << msg->angular_velocity.x << "," <<msg->angular_velocity.y<< "," << msg->angular_velocity.z;
    fil << "," << msg->linear_acceleration.x << "," <<msg->linear_acceleration.y<< "," << msg->linear_acceleration.z;
    fil << "," << roll << "," <<pitch<< "," << yaw;
    fil.close();
    //ROS_INFO("Imu Seq: [%d]", msg->header.seq);
    // ROS_INFO("Imu Orientation x: [%f], y: [%f], z: [%f]", msg->angular_velocity.x,msg->angular_velocity.y,msg->angular_velocity.z);
  }
void gpscb(const sensor_msgs::NavSatFix::ConstPtr& msg)	///callback for /mavros/global_position/globaldata subscription
  {
    std::ofstream fil;
    fil.open(path, std::fstream::app);
    fil << "," << msg->latitude << "," <<msg->longitude;
    fil.close();
    //ROS_INFO("gps Seq: [%f]", msg->latitude);
  }
void altcb(const std_msgs::Float64::ConstPtr& msg) 	///callback for /mavros/global_position/rel_alt
  {
    std::ofstream fil;
    fil.open(path, std::fstream::app);
    fil << "," << msg->data<< "\n";
    fil.close();
    ROS_INFO("HELLO");
    //ROS_INFO(typeid(&(msg->data)).name());
  } 
int main(int argc,char** argv )
{

    std::ofstream headings;
    headings.open(path, std::fstream::app);
    headings << "\n"<<"seq" <<","<<"angvel_x"<<","<<"angvel_y"<<","<<"angvel_z"<<","<<"linearacc_x"<<","<<"linearacc_y"<<","<<"linearacc_z"<< "," 
    << "orient_roll" << ","<<"orient_pitch"<<","<<"orient_yaw"<<","<<"lat"<<","<<"long"<<","<<"rel_alt"<<"\n";
    headings.close();
    ros::init(argc,argv,"flightlogger");
    ros::NodeHandle nh;
    ros::Subscriber imusub = nh.subscribe("mavros/imu/data",1,imucb);
    ros::Subscriber gpssub =nh.subscribe("mavros/global_position/global",1,gpscb);
    ros::Subscriber altsub = nh.subscribe("mavros/global_position/rel_alt",1,altcb);

    //ros::Subscriber rpysub = nh.subscribe("euler",1,rpycb);
  //  ros::Subscriber timesub= nh.subscribe("rosout",1,timecb);
    //message_filters::Subscriber<sensor_msgs::Imu> imu_sub(nh, "mavros/imu/data", 1);
    //message_filters::Subscriber<geometry_msgs::Vector3> rpy_sub(nh, "euler", 1);
    //message_filters::TimeSynchronizer<sensor_msgs::Imu, geometry_msgs::Vector3> sync(imu_sub, rpy_sub, 10);
    //sync.registerCallback(boost::bind(&callback, _1, _2));
    ros::spin();


}
