// Generated by gencpp from file example_ros_service/ExampleServiceMsgResponse.msg
// DO NOT EDIT!


#ifndef EXAMPLE_ROS_SERVICE_MESSAGE_EXAMPLESERVICEMSGRESPONSE_H
#define EXAMPLE_ROS_SERVICE_MESSAGE_EXAMPLESERVICEMSGRESPONSE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace example_ros_service
{
template <class ContainerAllocator>
struct ExampleServiceMsgResponse_
{
  typedef ExampleServiceMsgResponse_<ContainerAllocator> Type;

  ExampleServiceMsgResponse_()
    : on_the_list(false)
    , good_guy(false)
    , age(0)
    , nickname()  {
    }
  ExampleServiceMsgResponse_(const ContainerAllocator& _alloc)
    : on_the_list(false)
    , good_guy(false)
    , age(0)
    , nickname(_alloc)  {
  (void)_alloc;
    }



   typedef uint8_t _on_the_list_type;
  _on_the_list_type on_the_list;

   typedef uint8_t _good_guy_type;
  _good_guy_type good_guy;

   typedef int32_t _age_type;
  _age_type age;

   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _nickname_type;
  _nickname_type nickname;





  typedef boost::shared_ptr< ::example_ros_service::ExampleServiceMsgResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::example_ros_service::ExampleServiceMsgResponse_<ContainerAllocator> const> ConstPtr;

}; // struct ExampleServiceMsgResponse_

typedef ::example_ros_service::ExampleServiceMsgResponse_<std::allocator<void> > ExampleServiceMsgResponse;

typedef boost::shared_ptr< ::example_ros_service::ExampleServiceMsgResponse > ExampleServiceMsgResponsePtr;
typedef boost::shared_ptr< ::example_ros_service::ExampleServiceMsgResponse const> ExampleServiceMsgResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::example_ros_service::ExampleServiceMsgResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::example_ros_service::ExampleServiceMsgResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::example_ros_service::ExampleServiceMsgResponse_<ContainerAllocator1> & lhs, const ::example_ros_service::ExampleServiceMsgResponse_<ContainerAllocator2> & rhs)
{
  return lhs.on_the_list == rhs.on_the_list &&
    lhs.good_guy == rhs.good_guy &&
    lhs.age == rhs.age &&
    lhs.nickname == rhs.nickname;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::example_ros_service::ExampleServiceMsgResponse_<ContainerAllocator1> & lhs, const ::example_ros_service::ExampleServiceMsgResponse_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace example_ros_service

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsFixedSize< ::example_ros_service::ExampleServiceMsgResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::example_ros_service::ExampleServiceMsgResponse_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::example_ros_service::ExampleServiceMsgResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::example_ros_service::ExampleServiceMsgResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::example_ros_service::ExampleServiceMsgResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::example_ros_service::ExampleServiceMsgResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::example_ros_service::ExampleServiceMsgResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "fd72ed5c5735aa1bfe1d1f90d9319a65";
  }

  static const char* value(const ::example_ros_service::ExampleServiceMsgResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xfd72ed5c5735aa1bULL;
  static const uint64_t static_value2 = 0xfe1d1f90d9319a65ULL;
};

template<class ContainerAllocator>
struct DataType< ::example_ros_service::ExampleServiceMsgResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "example_ros_service/ExampleServiceMsgResponse";
  }

  static const char* value(const ::example_ros_service::ExampleServiceMsgResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::example_ros_service::ExampleServiceMsgResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "bool on_the_list\n"
"bool good_guy\n"
"int32 age\n"
"string nickname\n"
;
  }

  static const char* value(const ::example_ros_service::ExampleServiceMsgResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::example_ros_service::ExampleServiceMsgResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.on_the_list);
      stream.next(m.good_guy);
      stream.next(m.age);
      stream.next(m.nickname);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct ExampleServiceMsgResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::example_ros_service::ExampleServiceMsgResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::example_ros_service::ExampleServiceMsgResponse_<ContainerAllocator>& v)
  {
    s << indent << "on_the_list: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.on_the_list);
    s << indent << "good_guy: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.good_guy);
    s << indent << "age: ";
    Printer<int32_t>::stream(s, indent + "  ", v.age);
    s << indent << "nickname: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.nickname);
  }
};

} // namespace message_operations
} // namespace ros

#endif // EXAMPLE_ROS_SERVICE_MESSAGE_EXAMPLESERVICEMSGRESPONSE_H
