#pragma once

#include <geometry_msgs/geometry_msgs/msg/twist.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/subscription.hpp>
#include <rerun.hpp>
#include <rerun/recording_stream.hpp>
#include <std_srvs/srv/empty.hpp>
#include <turtlesim/msg/detail/pose__struct.hpp>
#include <turtlesim/msg/pose.hpp>

#include "point_stabilizer.h"
#include "trajectory_tracker.h"
#include "turtle_nav/srv/follow_path.hpp"
#include "turtle_nav/srv/go_to.hpp"

class TurtleNav final : public rclcpp::Node {
 public:
  TurtleNav();
  ~TurtleNav() override = default;

 private:
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
  rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr subscriber_;
  rclcpp::Service<turtle_nav::srv::GoTo>::SharedPtr goto_service_;
  rclcpp::Service<turtle_nav::srv::FollowPath>::SharedPtr follow_path_service_;
  rclcpp::Service<std_srvs::srv::Empty>::SharedPtr cancel_service_;
  rerun::RecordingStream rec_;

  turtlesim::msg::Pose::SharedPtr current_pose_;
  PointStabilizer point_stabilizer_;
  TrajectoryTracker trajectory_tracker_;
  std::vector<rerun::Position2D> real_traj_;

  void go_to_callback();

  void follow_path_callback();

  void go_to(
    const std::shared_ptr<turtle_nav::srv::GoTo::Request>& request,
    const std::shared_ptr<turtle_nav::srv::GoTo::Response>& response
  );

  void follow_path(
    const std::shared_ptr<turtle_nav::srv::FollowPath::Request>& request,
    const std::shared_ptr<turtle_nav::srv::FollowPath::Response>& response
  );

  void cancel(
    const std::shared_ptr<std_srvs::srv::Empty::Request>& request,
    const std::shared_ptr<std_srvs::srv::Empty::Response>& response
  );
};
