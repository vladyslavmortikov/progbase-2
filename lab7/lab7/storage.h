#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "optional.h"
#include "lection.h"

using namespace std;

class Storage
{
 public:
//   virtual ~Storage() {}  // UPD (8.5.2019): added

   virtual bool load() = 0;
   virtual bool save() = 0;
   // students
   virtual vector<Lection> getAllLections(void) = 0;
   virtual optional<Lection> getLectionById(int student_id) = 0;
   virtual bool updateLection(const Lection &lection) = 0;
   virtual bool removeLection(int lection_id) = 0;
   virtual int insertLection(const Lection &lection) = 0;
};
