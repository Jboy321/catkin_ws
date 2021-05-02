
(cl:in-package :asdf)

(defsystem "example_ros_service-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "ExampleServiceMsg" :depends-on ("_package_ExampleServiceMsg"))
    (:file "_package_ExampleServiceMsg" :depends-on ("_package"))
  ))