#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <wchar.h>
#include <unistd.h>

#include <json/json.h>

static void die(char *msg) {
  fprintf(stdout, "%s", msg);
  exit (EXIT_FAILURE);
}


static void parseNode (xmlDocPtr doc, xmlNodePtr cur, json_object *jsonObject ) {


    /* json_object * jobj = json_object_new_object();

    json_object *jstring = json_object_new_string("Joys of Programming");

    json_object *jint = json_object_new_int(10);
    json_object *jboolean = json_object_new_boolean(1);
    json_object *jdouble = json_object_new_double(2.14);

    json_object *jarray = json_object_new_array();

    json_object *jstring1 = json_object_new_string("c");
    json_object *jstring2 = json_object_new_string("c++");
    json_object *jstring3 = json_object_new_string("php");

    json_object_array_add(jarray,jstring1);
    json_object_array_add(jarray,jstring2);
    json_object_array_add(jarray,jstring3);

    json_object_object_add(jobj,"Site Name", jstring);
    json_object_object_add(jobj,"Technical blog", jboolean);
    json_object_object_add(jobj,"Average posts per day", jdouble);
    json_object_object_add(jobj,"Number of posts", jint);
    json_object_object_add(jobj,"Categories", jarray); */

    cur = cur->xmlChildrenNode;

    while (cur != NULL) {

        xmlChar *value;

        if ((xmlStrcmp(cur->name, (const xmlChar *)"text"))){
            //value = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
            value = xmlNodeGetContent(cur->xmlChildrenNode);

            json_object *jsonValue = json_object_new_string((char *)value);
            json_object_object_add(jsonObject, (char *)cur->name, jsonValue);

            //printf("%s: %s\n", cur->name, value);

            xmlFree(value);
        }

        cur = cur->next;
    }


    return;
}

void parseXmlDocToJson(const char *docname, char *child, json_object *jsonResultList) {

    char approot[1024];
    if (getcwd(approot, sizeof(approot)) == NULL)
        die ("getcwd() error\n");

    xmlDocPtr doc;
    xmlNodePtr cur;

    char filepath[1024];

    sprintf(filepath, "%s%s", approot, docname);

    doc = xmlParseFile(filepath);

    if (doc == NULL )
        return;

    cur = xmlDocGetRootElement(doc);    //Gets the root element of the XML Doc

    if (cur == NULL) {
        xmlFreeDoc(doc);
        return;
    }

    cur = cur->xmlChildrenNode;

    while (cur != NULL) {

        if ((!xmlStrcmp(cur->name, (const xmlChar *)child))) {

            json_object *jsonObject = json_object_new_object();
            parseNode (doc, cur, jsonObject);

            json_object_array_add(jsonResultList,jsonObject);


        }

        cur = cur->next;

    }


    xmlFreeDoc(doc);

    return;
}


int main(int argc, char* argv[]) {

    const char docname[] = "/test_product/products.xml";

    json_object *jsonResultList = json_object_new_array();

    parseXmlDocToJson(docname, "product", jsonResultList);

    printf (" %s\n",json_object_to_json_string(jsonResultList));

    free(jsonResultList);

    return EXIT_SUCCESS;

}
