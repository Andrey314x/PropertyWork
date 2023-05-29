#include <iostream>
#include "Ijsonio.h"
#include "Property.h"
#include "Owner.h"
#include "TaxService.h"
#include <iomanip>
#include <conio.h>

Property* MakeProperty() {
    system("cls");
    cout << "Choose type: " << endl;
    cout << "1 - Appartment, 2 - Car, 3 - CountryHouse" << endl;
    int i;
    cin >> i;
    Property* h1;
    Property* h2;
    Property* h3;
    switch (i)
    {
    case 1: h1 = new Appartment(1, 1); h1->SetFromConsole(); return h1;
    case 2: h2 = new Car(1, 1); h2->SetFromConsole(); return h2;
    case 3: h3 = new CountryHouse(1, 1); h3->SetFromConsole(); return h3;
    default: return h1 = new Appartment(1, 1);
    }
}

void OwnerWork(Owner& own) {
    Property* x;
    while (true) {
        system("cls");
        cout << "1 - Show owner data " << endl;
        cout << "2 - Add Property " << endl;
        cout << "3 - Remove Property " << endl;
        cout << "4 - Calculate tax " << endl;
        cout << "5 - Back" << endl;

        int i;
        cin >> i;
        switch (i)
        {
        case 1: own.ShowConsole(); break;
        case 2: x = MakeProperty(); own.properties.push_back(x); break;
        case 3: int i; cout << "Enter index: "; cin >> i; own.properties.erase(own.properties.begin() + i); break;
        case 4: cout << "Owner summary tax: " << own.TaxSum(); break;
        case 5: return;
        default:break;
        }
        _getch();
    }
}
void TaxCalculation(TaxService t) {
    while (true) {
        system("cls");
        cout << "Choose statistic option:" << endl;
        cout << "1 - Get summ tax" << endl;
        cout << "2 - Get average tax" << endl;
        cout << "3 - Get minimum tax owner" << endl;
        cout << "4 - Get maximum tax owner" << endl;
        cout << "5 - Back" << endl;
        int i;
        cin >> i;
        switch (i)
        {
        case 1: cout << t.SumTaxs() << endl; break;
        case 2: cout << t.AverageTaxs() << endl; break;
        case 3: t.MinTaxs().ShowConsole(); cout << endl; break;
        case 4: t.MaxTaxs().ShowConsole(); cout << endl; break;
        case 5: return;
        default: break;
        }
        _getch();
    }
}

int main(int argc, char* argv[])
{
    int move;
    TaxService owners;
    if (argc == 3) {
        cout << argc << endl;
        cout << argv[1] << " " << argv[2] << endl;
        string a1 = argv[1];
        string a2 = argv[2];
        if (a1 == "input.json") {
            TaxService t(argv[1]);
            owners = t;
            cout << "Input - JSON" << endl;
        }
        if (a1== "input.xml") {
            xml_document xmldoc;
            xmldoc.load_file(argv[1]);
            owners.fromXML(xmldoc.child("Owners"));
            cout << "Input - XML" << endl;
        }
        if (a2 == "output.json") {
            owners.JsonTaxList(argv[2]);
            cout << "Output - JSON" << endl;
        }
        if (a2 == "output.xml") {
            xml_document xmlout;
            auto node = xmlout.append_child("Owners");
            owners.toXML(node);
            xmlout.save_file(argv[2]);
            cout << "Output - XML" << endl;
        }
    }

    else {
        while (true) {
            system("cls");
            cout << "Choise option:" << endl;
            cout << "1 - Get owner list" << endl;
            cout << "2 - Add owner" << endl;
            cout << "3 - Delete owner" << endl;
            cout << "4 - To owner" << endl;
            cout << "5 - Calculate owner's tax" << endl;
            cout << "6 - Form owners list from JSON" << endl;
            cout << "7 - Form owners list from XML" << endl;
            cout << "8 - Create JSON owners tax list" << endl;
            cout << "9 - Create XML owners tax list" << endl;
            cout << "10 - Exit program" << endl;
            int i;
            cin >> i;


            switch (i)
            {
            case 1: {
                for (int i = 0; i < owners.owners.size(); i++) {
                    cout << i << ":" << endl;
                    owners.owners[i].ShowConsole();
                    cout << endl;
                }
                break;
            }
            case 2: {
                string name, inn;
                cout << "Enter fullname: "; cin >> name;
                cout << "Enter INN: "; cin >> inn;
                Owner o(name, inn);
                owners.owners.push_back(o);
                break;
            }
            case 3: {
                cout << "Enter index: " << endl;
                int i;
                cin >> i;
                owners.owners.erase(owners.owners.begin() + i);
                break;
            }
            case 4: {
                cout << "Enter index: ";
                int i;
                cin >> i;
                OwnerWork(*&owners.owners[i]);
                break;
            }
            case 5: {
                TaxCalculation(owners);
                break;
            }
            case 6: {
                /*if (argc != 0) {
                    TaxService t(argv[1]);
                    owners = t;
                    break;
                }*/
                cout << "Enter input filename: ";
                string s;
                cin >> s;

                TaxService t(s);
                owners = t;
                break;
            }
            case 7: {
                /*if (argc != 0) {
                    TaxService t(argv[1]);
                    owners = t;
                    break;
                }*/
                cout << "Enter input filename: ";
                string s;
                cin >> s;

                xml_document xmldoc;
                xmldoc.load_file(s.c_str());
                owners.fromXML(xmldoc.child("Owners"));
                break;
            }
            case 8: {
                if (argc != 0) {
                    owners.JsonTaxList(argv[2]);

                    break;
                }
                cout << "Enter output filename: ";
                string s;
                cin >> s;
                owners.JsonTaxList(s);
                break;
            }
            case 9: {
                /*if (argc != 0) {
                    owners.JsonTaxList(argv[2]);

                    break;
                }*/
                cout << "Enter output filename: ";
                string s;
                cin >> s;
                xml_document xmlout;
                auto node = xmlout.append_child("Owners");
                owners.toXML(node);
                xmlout.save_file(s.c_str());
                break;
            }
            case 10: {
                return 0;
            }
            default:break;
            }
            _getch();
        }
    }
}
