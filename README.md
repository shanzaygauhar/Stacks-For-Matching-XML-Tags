# Stacks-For-Matching-XML-Tags
C++ code for matching tags and quotes in XML using struct as a datastructure.
## Execution
Clone the project and run it in Visual Studio. Provide the name of xml file as command line input.

## Functionality
The program will get an XML code in an input file and it should figure out if tags and quotes are properly matched or
not using stack. In case the tags are not properly matched the program reports following:
i) the first error,
ii) print the mismatched tag and
iii) inform the line number where the starting tag occurred.

The code handles the following features of XML
1. xml prolog (xml header)
2. xml tags (xml elements). The xml tags are case sensitive.
3. xml attribute
4. xml comments, start with <!-- and ends with -->
