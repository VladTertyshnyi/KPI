#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

#include <libxml/tree.h>
#include "../headers/director.h"
#include "../headers/xmlModule.h"

//----------------------------------->>> Private methods <<<-----------------------------------

static void xmlModule_DirectorFromXML(director_t *curDirector, xmlNode *curNode)
{
    char *data;

    // Get "name" string attribute
    data = (char *) xmlGetProp(curNode, (const xmlChar *)"Name");
    director_setName(curDirector, data);
    data = (char *) xmlGetProp(curNode, (const xmlChar *)"Surname");
    director_setSurname(curDirector, data);
    for (curNode = curNode->children; curNode != NULL; curNode = curNode->next)
    {
        // Get "id" field.
        if (!xmlStrcmp(curNode->name, (const xmlChar *)"Id"))
        {
            data = (char *)xmlNodeGetContent(curNode);
            director_setId(curDirector, atoi(data));
            continue;
        }
        // Get "investments" field.
        else if (!xmlStrcmp(curNode->name, (const xmlChar *)"Investments"))
        {
            data = (char *)xmlNodeGetContent(curNode);
            director_setInvestments(curDirector, atoi(data));
            continue;
        }
        // Get "Years" field.
        else if (!xmlStrcmp(curNode->name, (const xmlChar *)"Years"))
        {
            data = (char *)xmlNodeGetContent(curNode);
            director_setYears(curDirector, atof(data));
            continue;
        }
        // Get "Birthdate" field.
        else if (!xmlStrcmp(curNode->name, (const xmlChar *)"Birthdate"))
        {
            data = (char *)xmlNodeGetContent(curNode);
            director_setBirthDate(curDirector, data);
            continue;
        }
    }
}

//----------------------------------->>> Public methods <<<-----------------------------------



void xmlModule_parseDirector(director_t **directorSet)
{
    xmlDoc *doc = xmlReadFile(XML_FILE_PATH, "UTF-8", 0);
    if (NULL == doc)
    {
        xmlFreeDoc(doc);
        return;
    }
    xmlNode *xml_root = xmlDocGetRootElement(doc);
    xmlNode *curNode = xml_root->children;
    for (int i = 0; curNode != NULL; curNode = curNode->next)
    {
        if (!xmlStrcmp(curNode->name, (const xmlChar *)"director"))
        {
            xmlModule_DirectorFromXML(directorSet[i++], curNode);
        }
    }
    xmlFreeDoc(doc);
}

int xmlModule_countDirectors()
{
    xmlDoc *doc = xmlReadFile(XML_FILE_PATH, "UTF-8", 0);
    if (NULL == doc)
    {
        xmlFreeDoc(doc);
        return (-1);
    }
    xmlNode *xml_root = xmlDocGetRootElement(doc);
    xmlNode *curNode = xml_root->children;
    int amountOfDirectors;
    for (amountOfDirectors = 0; curNode != NULL; curNode = curNode->next)
    {
        if (!xmlStrcmp(curNode->name, (const xmlChar *)"director"))
        {
            amountOfDirectors++;
        }
    }
    xmlFreeDoc(doc);
    return (amountOfDirectors);
}
