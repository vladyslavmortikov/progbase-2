#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "optional.h"
#include "storage.h"

using std::string;
using std::vector;

class XmlStorage : public Storage
{
  const string dir_name_;

  vector<Lection> lections_;

  int getNewLectionId();
  int getNewTopicId();
  void print();

public:
  XmlStorage(const string &dir_name) : dir_name_(dir_name) {}
//   ~XmlStorage();

  bool load();
  bool save();

  // Lections
  vector<Lection> getAllLections(void);
  optional<Lection> getLectionById(int lection_id);
  bool updateLection(const Lection &Lection);
  bool removeLection(int lection_id);
  int insertLection(const Lection &Lection);
};
