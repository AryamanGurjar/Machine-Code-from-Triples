#include <iostream>
#include <string>
#include <stack>
#include <iomanip>

using namespace std;

string t1 = " ", t2 = " ", t3 = " ";
string S, postfix, infix;
char operation_sign[10];
int counter = 0;
char special;
string special_string;

bool isOperand(char x)
{
    return (x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z');
}
string infixConversion(string postfix)
{
    stack<string> infix;
    for (int i = 0; postfix[i] != '\0'; i++)
    {
        if (isOperand(postfix[i]))
        {
            string op(1, postfix[i]);
            infix.push(op);
        }
        else
        {
            string op1 = infix.top();
            infix.pop();
            string op2 = infix.top();
            infix.pop();
            infix.push("(" + op2 + postfix[i] + op1 + ")");
        }
    }
    return infix.top();
}

void for_T1(string b)
{
    int check = 0;
    if (b[0] == '-')
    {
        check = 1;
        operation_sign[counter] = '$';
        counter++;
        if (b[1] == '(')
        {
            int i = 2;
            infix[0] = '$';
            infix[1] = '$';
            infix[i] = '$';
            while (b[i] != ')')
            {
                if (b[i] == '+' || b[i] == '-' || b[i] == '*' || b[i] == '/')
                {
                    operation_sign[counter] = b[i];
                    counter++;
                }

                t1 = t1 + b[i];
                infix[i] = '$';
                i++;
            }
            infix[i] = '$';
            infix = infix.substr(i + 1);
        }
        else
        {
            t1 = b[1];
            infix[0] = '$';
            infix[1] = '$';
            infix = infix.substr(2);
        }
        special_string = infix;
        infix = infix.substr(1);
    }

    else if (b[0] == '(')
    {
        int i = 1;
        check = 1;
        infix[0] = '$';
        infix[i] = '$';
        while (b[i] != ')')
        {
            if (b[i] == '+' || b[i] == '-' || b[i] == '*' || b[i] == '/')
            {
                operation_sign[counter] = b[i];
                counter++;
            }
            t1 = t1 + b[i];
            infix[i] = '$';
            i++;
        }
        infix[i] = '$';
        infix = infix.substr(i + 1);
        special_string = infix;
        infix = infix.substr(1);
    }

    else
    {
        int i = 0;

        while (b[i] != '(')
        {
            i++;
            if (b[i] == '\0')
            {
                if (b.length() == 3)
                {
                    special = b[1];
                }

                goto check;
            }
        }
        infix[i] = '$';

        int start = i - 1;
        i++;
        while (b[i] != ')')
        {
            check = 1;
            if (b[i] == '+' || b[i] == '-' || b[i] == '*' || b[i] == '/')
            {
                operation_sign[counter] = b[i];
                counter++;
            }
            t1 = t1 + b[i];
            infix[i] = '$';
            i++;
        }
        infix[i] = '$';
        special_string = infix.erase(start + 1, i);
        infix = infix.erase(start, i);
    }

    if (check == 0)
    {
    check:

        if (b[1] == '+' || b[1] == '-')
        {
            t1 = b[0];
            infix[0] = '$';
            if (b[1] == '+' || b[1] == '-' || b[1] == '*' || b[1] == '/')
            {
                operation_sign[counter] = b[1];
                counter++;
            }
            if (b.length() == 3)
            {
                operation_sign[0] = 'X';
            }
            infix = infix.substr(1);
            special_string = infix;
            infix = infix.substr(1);
        }
    }

    // cout<<infix<<endl;
}

void for_T2(string b)
{
    if (b[0] == '(')
    {
        int i = 1;
        infix[0] = '$';
        infix[i] = '$';
        while (b[i] != ')')
        {
            if (b[i] == '+' || b[i] == '-' || b[i] == '*' || b[i] == '/')
            {
                operation_sign[counter] = b[i];
                counter++;
            }
            t2 = t2 + b[i];
            infix[i] = '$';
            i++;
        }
        infix[i] = '$';
        infix = infix.erase(0 + i);
    }
    else if (b[1] == '\0')
    {

        operation_sign[counter] = 'x';
        counter++;

        t2 = b[0];
        infix[0] = '$';
        infix.clear();
    }

    else
    {
    next:
        int i = 0;
        while (b[i] != '(')
        {
            i++;
        }
        infix[i] = '$';
        i++;
        while (b[i] != ')')
        {
            if (b[i] == '+' || b[i] == '-' || b[i] == '*' || b[i] == '/')
            {
                operation_sign[counter] = b[i];
                counter++;
            }
            t2 = t2 + b[i];
            infix[i] = '$';
            i++;
        }
        infix[i] = '$';
    }
    // cout<<infix<<endl;
}

int main()
{

    int t;
    cout << "==>";
    cin >> S;
    cout << "Postfix expression(directly infix press  NO): ";
    cin >> postfix;
    if (postfix == "NO" || postfix == "no")
    {
        cout << S << " = ";
        cin >> infix;
        goto jump;
    }

    infix = infixConversion(postfix);
    t = infix.size() - 1;
    infix = infix.substr(1, t - 1);

    cout << "\nInfix conversion :" << infix << endl;
    // return 0;
    cout << S << " = " << infix << endl;
jump:

    t3 = S;

    for_T1(infix);
    // for_T2(infix);
    // t2 = infix;
    // cout<<infix<<" "<<special_string<<endl;
    for (int j = 0; j < special_string.length(); j++)
    {
        if (special_string[j] == '+' || special_string[j] == '-' || special_string[j] == '*' || special_string[j] == '/')
        {
            if (special_string[j + 1] == '(')
            {
                special = special_string[j];
            }
            else if (special_string[j + 1] == '\0')
            {
                special = special_string[j];
            }
        }
    }
    for_T2(infix);

    operation_sign[counter] = '=';

    char a, b, c, d;

    for (int i = 0; t1[i] != '\0'; i++)
    {
        if (t1[i] == '+' || t1[i] == '-' || t1[i] == '*' || t1[i] == '/')
        {
            if (t1[i - 1] != '\0')
            {
                a = t1[i - 1];
            }
            else
            {
                a = 'X';
            }

            if (t1[i + 1] != '\0')
            {
                b = t1[i + 1];
            }
            else
            {
                b = 'X';
            }
        }
        else if (t1.size() == 1)
        {
            a = t1[0];
            b = 'X';
        }
    }

    for (int i = 0; t2[i] != '\0'; i++)
    {
        if (t2[i] == '+' || t2[i] == '-' || t2[i] == '*' || t2[i] == '/')
        {
            if (t2[i - 1] != '\0')
            {
                c = t2[i - 1];
            }
            else
            {
                c = 'X';
            }

            if (t2[i + 1] != '\0')
            {
                d = t2[i + 1];
            }
            else
            {
                d = 'X';
            }
        }
        else if (t2.size() == 1)
        {
            c = t2[0];
            d = 'X';
        }
    }
    if (operation_sign[0] == '$')
    {
        t1 = '-' + t1;
    }

    cout << "t1 = " << t1 << endl;
    cout << "t2 = " << t2 << endl;
    cout << "t3 = t1" << special << "t2" << endl;
    cout << S << " = t3" << endl;
    cout << endl
         << endl;

    int ch1 = 0, ch2 = 0;
    if (a != 'X')
    {
        cout << "LOAD R1," << a << endl;
    }
    if (b != 'X')
    {
        cout << "LOAD R2," << b << endl;
    }

    if (operation_sign[0] == '$')
    {
        cout << "NEG R1" << endl;
    }
    else if (operation_sign[0] == '+')
    {
        cout << "ADD R1,R2" << endl;
    }
    else if (operation_sign[0] == '-')
    {
        cout << "SUB R1,R2" << endl;
    }
    else if (operation_sign[0] == '*')
    {
        cout << "MUL R1,R2" << endl;
    }
    else if (operation_sign[0] == '/')
    {
        cout << "DIV R1,R2" << endl;
    }
    else if (operation_sign[0] == 'X')
    {
        cout << "STORE T1,R1" << endl;
        ch1 = 1;
    }

    if (ch1 == 0)
    {
        cout << "STORE T1,R1" << endl;
    }

    if (c != 'X')
    {
        cout << "LOAD R1," << c << endl;
    }
    if (d != 'X')
    {
        cout << "LOAD R2," << d << endl;
    }

    if (operation_sign[1] == '+')
    {
        cout << "ADD R1,R2" << endl;
    }
    else if (operation_sign[1] == '-')
    {
        cout << "SUB R1,R2" << endl;
    }
    else if (operation_sign[1] == '*')
    {
        cout << "MUL R1,R2" << endl;
    }
    else if (operation_sign[1] == '/')
    {
        cout << "DIV R1,R2" << endl;
    }
    else if (operation_sign[1] == 'X')
    {
        cout << "STORE T2,R1" << endl;
        ch2 = 1;
    }

    if (ch1 == 0)
    {
        cout << "STORE T2,R1" << endl;
    }
    // for t1+t2

    cout << "LOAD R1,T1" << endl;
    cout << "LOAD R2,T2" << endl;

    if (special == '+')
    {
        cout << "ADD R1,R2" << endl;
    }
    else if (special == '-')
    {
        cout << "SUB R1,R2" << endl;
    }
    else if (special == '*')
    {
        cout << "MUL R1,R2" << endl;
    }
    else if (special == '/')
    {
        cout << "DIV R1,R2" << endl;
    }

    cout << "STORE T3,R1" << endl;

    cout << "LOAD R4,T3" << endl;

    cout << "STORE " << S << ",R4" << endl;

    return 0;
}