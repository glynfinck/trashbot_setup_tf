#include <ros/ros.h>
#include <tf/transform_listener.h>

int main(int argc, char** argv){
  ros::init(argc, argv, "my_tf_listener");

  ros::NodeHandle node;

  tf::TransformListener listener;
  listener.waitForTransform("/map", "/odom",
                                ros::Time::now(), ros::Duration(10.0));
  listener.waitForTransform("/odom", "/camera_link",
                                ros::Time::now(), ros::Duration(10.0));
  listener.waitForTransform("/camera_link", "/camera_depth_frame",
                                ros::Time::now(), ros::Duration(10.0));
                     
  ros::Rate rate(10.0);
  while (node.ok()){
    tf::StampedTransform transform_map;
    tf::StampedTransform transform_odom;
    tf::StampedTransform transform_camera;

    try{
      ros::Time now = ros::Time::now();
      listener.lookupTransform("/map", "/odom",
                             now, transform_map);
      listener.lookupTransform("/odom", "/camera_link",
                             now, transform_odom);
      listener.lookupTransform("/camera_link", "/camera_depth_frame",
                             now, transform_camera);
    }
    catch (tf::TransformException ex){
      ROS_ERROR("%s",ex.what());
      ros::Duration(1.0).sleep();
    }
    std::cout <<"x=" << transform_map.getOrigin().x() << "   y=" << transform_map.getOrigin().y() << std::endl;
    std::cout <<"x=" << transform_odom.getOrigin().x() << "   y=" << transform_odom.getOrigin().y() << std::endl;
    std::cout <<"x=" << transform_camera.getOrigin().x() << "   y=" << transform_camera.getOrigin().y() << std::endl;
    std::cout << std::endl;
    rate.sleep();
  }
  return 0;
};