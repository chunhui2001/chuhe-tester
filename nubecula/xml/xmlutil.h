#ifndef xmlutil_h__
#define xmlutil_h__


#include <json/json.h>

void parseXmlDocToJson(const char *docname, char *child, json_object *jsonResultList);


#endif //
