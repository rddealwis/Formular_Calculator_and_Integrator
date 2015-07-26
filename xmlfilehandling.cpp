#include "xmlfilehandling.h"
#include <QtXml>
#include <QDebug>
#include <string>
XMLFileHandling::XMLFileHandling()
{

}

XMLFileHandling::~XMLFileHandling()
{

}

void ListElements(QDomElement root, QString tagName, QString attribute, std::string formula[], std::string formulaName[], bool operation, int temp);

bool XMLFileHandling::Write(std::string fileName, std::string formula[], std::string formulaName[])
{
    QString qFileName=QString::fromStdString(fileName);
    QDomDocument document;
    QDomElement root=document.createElement("SavedFormulaEx");
    document.appendChild(root);

    for(int i=0; formula[i] != ""; i++)
    {
        QDomElement book =document.createElement("Formulae");
        book.setAttribute("Name", QString::fromStdString(formulaName[i]));
        root.appendChild(book);
        QDomElement chapter =document.createElement("Formula");
        chapter.setAttribute("Value", QString::fromStdString(formula[i]));
        book.appendChild(chapter);
    }
    QFile file(qFileName);

    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        return false;
    }
    else
    {
        QTextStream stream (&file);
        stream<<document.toString();
        file.close();

        return true;
    }
}

bool XMLFileHandling::Read(std::string& fileName,std::string formula[],std::string formulaName[])
{
    QDomDocument document;
    QString qFileName=QString::fromStdString(fileName);
    QFile file(qFileName);

    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        return false;
    }
    else
    {
        if(!document.setContent(&file))
        {
        }
        file.close();
    }

    try
    {
        QDomElement root = document.firstChildElement();
        ListElements(root, "Formulae", "Name", formula, formulaName, true, 0);
        QDomNodeList books=root.elementsByTagName("Formulae");

        for(int i=0; i < books.count(); i++)
        {
            QDomNode booknode = books.at(i);
            if(booknode.isElement())
            {
                QDomElement book=booknode.toElement();
                ListElements(book, "Formula", "Value", formula, formulaName, false, i);
            }
        }
    }
    catch(...)
    {
        return false;
    }
    return true;
}

void ListElements(QDomElement root, QString tagName, QString attribute, std::string formula[], std::string formulaName[], bool operation, int temp)
{
    QDomNodeList items=root.elementsByTagName(tagName);

    for(int i=0; i < items.count(); i++)
    {
        QDomNode itemNode = items.at(i);

        if(itemNode.isElement())
        {
            QDomElement itemElement = itemNode.toElement();

            if(operation)
            {
                formulaName[i]=itemElement.attribute(attribute).toStdString();
            }

            else
            {
                formula[temp]=itemElement.attribute(attribute).toStdString();
            }
        }
    }
}
