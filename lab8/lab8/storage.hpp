#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "optional.hpp"
#include "lection.hpp"
#include "topics.hpp"

using namespace std;

class Storage
{
 public:
   virtual ~Storage() {}

   virtual bool open() = 0;
   virtual bool close() = 0;
   // students
   virtual vector<Lection> getAllLections(void) = 0;
   virtual optional<Lection> getLectionById(int student_id) = 0;
   virtual bool updateLection(const Lection &lection) = 0;
   virtual bool removeLection(int lection_id) = 0;
   virtual int insertLection(const Lection &lection) = 0;
   // courses
   virtual vector<Topic> getAllTopics(void) = 0;
   virtual optional<Topic> getTopicById(int topic_id) = 0;
   virtual bool updateTopic(const Topic &topic) = 0;
   virtual bool removeTopic(int topic_id) = 0;
   virtual int insertTopic(const Topic &topic) = 0;
};
