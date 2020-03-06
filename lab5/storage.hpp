#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "optional.hpp"
#include "lection.hpp"
#include "topics.hpp"
#include "csv.hpp"

using std::string;
using std::vector;

class Storage
{
  const string dir_name_;

  vector<Lection> lections_;
  vector<Topic> topics_;

  int getNewLectionId();
  int getNewTopicId();
  void print();

public:
  Storage(const string &dir_name) : dir_name_(dir_name) {}

  bool load();
  bool save();

  // Lections
  vector<Lection> getAllLections(void);
  optional<Lection> getLectionById(int lection_id);
  bool updateLection(const Lection &Lection);
  bool removeLection(int lection_id);
  int insertLection(const Lection &Lection);

//Topics
  vector<Topic> getAllTopics(void);
  optional<Topic> getTopicById(int topic_id);
  bool updateTopic(const Topic &topic);
  bool removeTopic(int topic_id);
  int insertTopic(const Topic &topic);
};
