#ifndef XMLFILEHANDLING_H
#define XMLFILEHANDLING_H
#include <qmessagebox.h>

class XMLFileHandling
{
public:
    XMLFileHandling();
    ~XMLFileHandling();
    bool Write(std::string fileName, std::string formula[], std::string formulaName[]);
    bool Read(std::string &fileName, std::string formula[], std::string formulaName[]);
};

#endif // XMLFILEHANDLING_H
