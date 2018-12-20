#include <../../lib/michaelvectors.h>
#include <entry.h>
#ifndef FILEOUTPUT_H
#define FILEOUTPUT_H


class fileOutput
{
public:
    fileOutput(const char **&, michaelVector<entry> & ); //function to output enteries michaelVector to output file
    void clearFile(const char **&argv); //function to clear out contents of output file
    char c = ' ';
};

#endif // FILEOUTPUT_H
