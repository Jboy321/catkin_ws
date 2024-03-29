// Generated by gencpp from file example_action_server/demoFeedback.msg
// DO NOT EDIT!


#ifndef EXAMPLE_ACTION_SERVER_MESSAGE_DEMOFEEDBACK_H
#define EXAMPLE_ACTION_SERVER_MESSAGE_DEMOFEEDBACK_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace example_action_server
{
template <class ContainerAllocator>
struct demoFeedback_
{
  typedef demoFeedback_<ContainerAllocator> Type;

  demoFeedback_()
    : fdbk(0)  {
    }
  demoFeedback_(const ContainerAllocator& _alloc)
    : fdbk(0)  {
  (void)_alloc;
    }



   typedef int32_t _fdbk_type;
  _fdbk_type fdbk;





  typedef boost::shared_ptr< ::example_action_server::demoFeedback_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::example_action_server::demoFeedback_<ContainerAllocator> const> ConstPtr;

}; // struct demoFeedback_

typedef ::example_action_server::demoFeedback_<std::allocator<void> > demoFeedback;

typedef boost::shared_ptr< ::example_action_server::demoFeedback > demoFeedbackPtr;
typedef boost::shared_ptr< ::example_action_server::demoFeedback const> demoFeedbackConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::example_action_server::demoFeedback_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::example_action_server::demoFeedback_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::example_action_server::demoFeedback_<ContainerAllocator1> & lhs, const ::example_action_server::demoFeedback_<ContainerAllocator2> & rhs)
{
  return lhs.fdbk == rhs.fdbk;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::example_action_server::demoFeedback_<ContainerAllocator1> & lhs, const ::example_action_server::demoFeedback_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace example_action_server

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsFixedSize< ::example_action_server::demoFeedback_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::example_action_server::demoFeedback_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::example_action_server::demoFeedback_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::example_action_server::demoFeedback_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::example_action_server::demoFeedback_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::example_action_server::demoFeedback_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::example_action_server::demoFeedback_<ContainerAllocator> >
{
  static const char* value()
  {
    return "46cc8f8da6ebf35aedc6bad2e96b2e59";
  }

  static const char* value(const ::example_action_server::demoFeedback_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x46cc8f8da6ebf35aULL;
  static const uint64_t static_value2 = 0xedc6bad2e96b2e59ULL;
};

template<class ContainerAllocator>
struct DataType< ::example_action_server::demoFeedback_<ContainerAllocator> >
{
  static const char* value()
  {
    return "example_action_server/demoFeedback";
  }

  static const char* value(const ::example_action_server::demoFeedback_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::example_action_server::demoFeedback_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n"
"#feedback\n"
"int32 fdbk\n"
;
  }

  static const char* value(const ::example_action_server::demoFeedback_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::example_action_server::demoFeedback_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.fdbk);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct demoFeedback_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::example_action_server::demoFeedback_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::example_action_server::demoFeedback_<ContainerAllocator>& v)
  {
    s << indent << "fdbk: ";
    Printer<int32_t>::stream(s, indent + "  ", v.fdbk);
  }
};

} // namespace message_operations
} // namespace ros

#endif // EXAMPLE_ACTION_SERVER_MESSAGE_DEMOFEEDBACK_H
