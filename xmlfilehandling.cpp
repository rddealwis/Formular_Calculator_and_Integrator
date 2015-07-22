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
    //Make the root element
    QDomElement root=document.createElement("SavedFormulaEx");
    //Add it to the document
    document.appendChild(root);
    //Add some elements

    for(int i=0; i<formula->length()+1; i++)
    {
        QDomElement book =document.createElement("Formulae");
        book.setAttribute("Name", QString::fromStdString(formulaName[i]));
        root.appendChild(book);
        QDomElement chapter =document.createElement("Formula");
        chapter.setAttribute("Value", QString::fromStdString(formula[i]));
        book.appendChild(chapter);
    }
    //write tothe file
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
    //Load the file
    QFile file(qFileName);

    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {        
        return false;
    }
    else
    {
        if(!document.setContent(&file))
        {            
            return false;
        }
        file.close();
    }

    //Get the root element
    QDomElement root = document.firstChildElement();

    //List the books

    ListElements(root, "Formulae", "Name", formula, formulaName, true, 0);

    //Get the chapters

   QDomNodeList books=root.elementsByTagName("Formulae");

    for(int i=0; i < books.count(); i++)
    {
        QDomNode booknode = books.at(i);

        //convert to an element
        if(booknode.isElement())
        {
            QDomElement book=booknode.toElement();
            ListElements(book, "Formula", "Value", formula, formulaName, false, i);
        }
    }

    //std::cout<<"Finished Reading File";

    return true;
}

void ListElements(QDomElement root, QString tagName, QString attribute, std::string formula[], std::string formulaName[], bool operation, int temp)
{
    QDomNodeList items=root.elementsByTagName(tagName);
    std::string values="";
    QMessageBox xmlContent;

    for(int i=0; i < items.count(); i++)
    {
        QDomNode itemNode = items.at(i);

        //convert to element

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

            /*values+=formulaName[i];

            xmlContent.setText("XML Content.");
            xmlContent.setInformativeText(QString::fromStdString(values));
            xmlContent.setStandardButtons(QMessageBox::Ok);
            xmlContent.setDefaultButton(QMessageBox::Ok);
*/
            //qDebug()<<itemElement.attribute(attribute);
        }
    }
    //int ret = xmlContent.exec();
}
