#include <iostream>
using namspace std;
int main()
{
    Parser parser;
    try
    {
        parser.parse();
    }
    catch (const std::invalid_argument ia)
    {
        std::cout << ia.what() << std::endl;
    }
    return 0;
}
class Parser
{
public:
    Parser()
    {
        std::string str;
        std::cout << "Enter infix string : ";
        std::cin >> str;
        stream = std::stringstream(str);
        lookahead = stream.get();
    }

    void parse()
    {
        expr();
        print_translated_string();
    }

private:
    char lookahead;
    std::string translated;
    std::stringstream stream;

    void display(char terminal)
    {
        translated += terminal;
    }

    void print_translated_string()
    {
        std::cout << translated << std::endl;
    }

    std::string error_message(char lookahead)
    {
        return "Syntax error near " + std::string(1, lookahead);
    }

    void match(char terminal)
    {
        if (terminal == lookahead)
        {
            lookahead = stream.get();
        }
        else
        {
            throw std::invalid_argument(error_message(lookahead));
        }
    }

    void digit()
    {
        display(lookahead);
        match(lookahead);
    }

    void factor()
    {
        if (isdigit(lookahead))
        {
            digit();
        }
        else if (lookahead == '(')
        {
            match('(');
            expr();
            match(')');
        }
        else
        {
            throw std::invalid_argument(error_message(lookahead));
        }
    }

    void term()
    {
        factor();

        while (true)
        {
            if (lookahead == '*')
            {
                match('*');
                factor();
                display('*');
            }
            else if (lookahead == '/')
            {
                match('/');
                factor();
                display('/');
            }
            else
            {
                return;
            }
        }
    }

    void expr()
    {
        term();

        while (true)
        {
            if (lookahead == '+')
            {
                match('+');
                term();
                display('+');
            }
            else if (lookahead == '-')
            {
                match('-');
                term();
                display('-');
            }
            else
            {
                return;
            }
        }
    }
};