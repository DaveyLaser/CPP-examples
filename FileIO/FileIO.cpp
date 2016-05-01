#include <iostream>
#include <string>
#include <fstream>

using namespace std;


float getPrice( string inputLine )
{
    auto position = inputLine.find( "$" );

    if( position <= inputLine.size() )
    {
        return stod( inputLine.substr( position + 1 ) );
    }

    return 0;
}

string getBarCode( string inputLine )
{
    auto position = inputLine.find( '$' );

    position -= 1;

    string barCode;

    while( isspace( inputLine[ position ] ) )
    {
        --position;
    }

    while( ! isspace( inputLine[ position ] ) )
    {
        barCode.insert( barCode.begin(), inputLine[ position-- ] );
    }

    return barCode;
}

int main( int argc, char** argv )
{
    cout << "Enter barcode: " << endl;

    string barcodeInput;
    getline( cin, barcodeInput );

    ifstream inputFile( "../FileIO/File.txt" );

    if( inputFile.is_open() )
    {
        string inputLine;

        while( getline( inputFile, inputLine) )
        {
            auto price = getPrice( inputLine );

            if( price != 0 )
            {
                if( getBarCode( inputLine ) == barcodeInput )
                {
                    cout << "Price: " << price << endl;

                    inputFile.close();

                    return 0;
                }
            }
        }

        cout << "No matching barcode." << endl;

        inputFile.close();
    }

    return 0;
}
