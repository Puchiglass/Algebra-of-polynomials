#include "polynom.h"
#include "eq_exception.h"
#include "list.h"
#include <fstream>
#include <cmath>
#include <istream>
#include <ostream>
#include <sstream>
#include <string>
#include <fstream>

Monom& Monom::operator+=(const Monom& other)
{
    if (deg != other.deg)
        throw EqException(error_codes::k_INCORRECT_OPERATION);
    coef += other.coef;
    return *this;
}

Monom& Monom::operator-=(const Monom& other)
{
    if (deg != other.deg)
        throw EqException(error_codes::k_INCORRECT_OPERATION);
    coef -= other.coef;
    return *this;
}

Monom& Monom::operator*=(const Monom& other)
{
    coef *= other.coef;
    deg += other.deg;
    return *this;
}

Monom& Monom::operator*=(double num)
{
    coef *= num;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Monom& mnm)
{
    int c = mnm.deg % BASE;
    int b = ((mnm.deg - c) / BASE) % BASE;
    int a = ((mnm.deg - b - c) / BASE / BASE);
    std::string out;

    if (a + b + c == 0) {
        os << std::to_string(mnm.coef);
        return os;
    }

    out += std::to_string(mnm.coef);

    if (a != 0)
        out += "x" + std::to_string(a);
    if (b != 0)
        out += "y" + std::to_string(b);
    if (c != 0)
        out += "z" + std::to_string(c);
    os << out;
    return os;
}

std::istream& operator>>(std::istream& is, Monom& mnm)
{
    std::string smon;
    is >> smon;
    int i = 0;
    std::string tmp;

    // Search coefficient
    while (char c = smon[i]) {
        if (c == 'x' || c == 'y' || c == 'z')
            break;
        tmp += c;
        i++;
    }

    if (tmp == "-") {
        mnm.coef = -1.0;
    }
    else if (tmp.size() > 0) {
        mnm.coef = std::stod(tmp);
    }
    else {
        mnm.coef = 1.0;
    }

    // Search deg`s
    tmp.clear();


    if (smon.size() - i == 0)
        mnm.deg = 0;

    for (int j = i; j < smon.size(); j++) {
        if (smon[j] == 'x') {
            for (int k = j + 1; k < smon.size(); k++) {
                if (k < smon.size()) {
                    if (smon[k] == 'y' || smon[k] == 'z') {
                        break;
                    }
                    tmp += smon[k];
                }
            }
            if (!tmp.size()) {
                mnm.deg += 1 * BASE * BASE;
            }
            else {
                mnm.deg += std::stoi(tmp) * BASE * BASE;
                tmp.clear();
            }
        }

        else if (smon[j] == 'y') {
            for (int k = j + 1; k < smon.size(); k++) {
                if (k < smon.size()) {
                    if (smon[k] == 'z') {
                        break;
                    }
                    tmp += smon[k];
                }
            }
            if (!tmp.size()) {
                mnm.deg += 1 * BASE;
            }
            else {
                mnm.deg += std::stoi(tmp) * BASE;
                tmp.clear();
            }
        }

        else if (smon[j] == 'z') {
            for (int k = j + 1; k < smon.size(); k++) {
                tmp += smon[k];
            }
            if (!tmp.size()) {
                mnm.deg += 1;
            }
            else {
                mnm.deg += std::stoi(tmp);
            }
        }
    }
    return is;
}

std::string Monom::str()const
{
    std::string tmp;
    if (coef > 0)
        tmp.push_back('+');
    std::ostringstream os;
    os << coef;
    int tmp_deg = deg;
    int c = tmp_deg % 10;
    tmp_deg /= 10;
    int b = tmp_deg % 10;
    tmp_deg /= 10;
    int a = tmp_deg % 10;
    if (a > 0)
    {
        os << 'x';
        if (a != 1)
            os << a;
    }
    if (b > 0)
    {
        os << 'y';
        if (b != 1)
            os << b;
    }
    if (c > 0)
    {
        os << 'z';
        if (c != 1)
            os << c;
    }
    tmp += os.str();
    return tmp;
}

Monom Monom::integral(char param)
{
    Monom tmp(*this);
    if (param == 'x')
    {
        if (deg / 100 != 9)
        {
            tmp.deg += 100;
            tmp.coef = tmp.coef / (tmp.deg / 100);
        }
    }
    if (param == 'y')
    {
        if ((deg % 100) % 10 != 9)
        {
            tmp.deg += 10;
            tmp.coef = tmp.coef / ((tmp.deg % 100) % 10);
        }
    }
    if (param == 'z')
    {
        if (deg % 10 != 9)
        {
            tmp.deg += 1;
            tmp.coef = tmp.coef / (tmp.deg % 10);
        }
    }
    return tmp;
}

Monom Monom::derivative(char param)
{
    Monom tmp(*this);
    if (param == 'x')
    {
        if (deg / 100 != 0)
        {
            tmp.deg -= 100;
            tmp.coef = tmp.coef * (deg / 100);
        }
        else tmp.coef = 0;
    }
    if (param == 'y')
    {
        if ((deg % 100) % 10 != 0)
        {
            tmp.deg -= 10;
            tmp.coef = tmp.coef * ((deg % 100) % 10);
        }
        else tmp.coef = 0;
    }
    if (param == 'z')
    {
        if (deg % 10 != 0)
        {
            tmp.deg -= 1;
            tmp.coef = tmp.coef * (deg % 10);
        }
        else tmp.coef = 0;
    }
    return tmp;
}

Monom operator+(const Monom& lhs, const Monom& rhs)
{
    Monom tmp(lhs);
    return (tmp += rhs);
}

Monom operator-(const Monom& lhs, const Monom& rhs)
{
    Monom tmp(lhs);
    return (tmp -= rhs);
}

Monom operator*(const Monom& lhs, const Monom& rhs)
{
    Monom tmp(lhs);
    return (tmp *= rhs);
}

Monom operator*(double lhs, const Monom& rhs)
{
    Monom tmp(rhs);
    return (tmp *= lhs);
}

Monom operator*(const Monom& lhs, double rhs)
{
    Monom tmp(lhs);
    return (tmp *= rhs);
}

bool Monom::operator<(const Monom& other) const
{
    return deg > other.deg;
}

void Polynom::add_monom(const Monom& monom)
{
    polynom.add(monom);
}

Polynom::Polynom(std::string polynom_str)
{
    std::istringstream is(polynom_str);
    operator>>(is, *this);
}


std::ostream& operator<<(std::ostream& os, const Polynom& pl)
{
    if (pl.polynom.get_size() == 0) {
        os << "0";
        return os;
    }

    int c = pl.polynom.get_size();

    for (List<Monom>::iterator it = pl.polynom.begin();
        it != pl.polynom.end(); ++it)
    {
        if (it != pl.polynom.begin()) {
            if ((*it).get_coef() > 0) {
                std::cout << "+";
            }
        }
        os << *it;
    }

    return os;
}

std::istream& operator>>(std::istream& is, Polynom& pl)
{
    std::string polynom_str;

    pl.polynom.erase_list();

    std::string tmp;
    while (is >> tmp) {
        polynom_str += tmp;
    }
    tmp.clear();


    // Delete spaces 
    polynom_str.erase(std::remove(polynom_str.begin(), polynom_str.end(), ' '), polynom_str.end());

    int i = 0;
    bool mflag = false;
    while (char c = polynom_str[i]) {
        if (c == '+') {
            if (i != 0) {
                if (mflag) {
                    mflag = false;
                    tmp.insert(0, std::string("-"));
                }
                std::istringstream istr(tmp);
                Monom tmon;
                operator>>(istr, tmon);
                pl.polynom.add(tmon);
                tmp.clear();
            }
        }
        else if (c == '-') {
            if (i == 0) {
                mflag = true;
                i++;
                continue;
            }

            if (mflag) {
                tmp.insert(0, std::string("-"));
            }

            std::istringstream istr(tmp);
            Monom tmon;
            operator>>(istr, tmon);
            pl.polynom.add(tmon);
            tmp.clear();
            mflag = true;
        }
        else {
            tmp += c;
        }
        i++;
    }
    if (mflag) {
        tmp.insert(0, std::string("-"));
    }
    std::istringstream istr(tmp);
    Monom tmon;
    operator>>(istr, tmon);
    pl.polynom.add(tmon);

    pl.optimize_polynom();
    return is;
}

std::string Polynom::str()const
{
    std::string tmp{ "" };
    Monom tp;
    for (List<Monom>::iterator it = polynom.begin();
        it != polynom.end(); ++it)
    {
        tp = *it;
        tmp += tp.str();
    }
    return tmp;
}


Polynom Polynom::sort(const Polynom& pl) const
{
    std::vector<Monom> vec_tmp;
    for (List<Monom>::iterator it = pl.polynom.begin();
        it != pl.polynom.end(); ++it)
    {
        vec_tmp.push_back(*it);
    }
    std::sort(vec_tmp.begin(), vec_tmp.end());
    Polynom tpoly;
    for (Monom& tmp : vec_tmp) {
        tpoly.add_monom(tmp);
    }
    return tpoly;
}

void Polynom::optimize_polynom()
{
    bool flag = false;
    List<Monom>::iterator it3 = polynom.begin();
    for (List<Monom>::iterator it1 = polynom.begin(); it1 != polynom.end(); ++it1) {

        if (flag) {
            polynom.erase(it3);
            flag = false;
        }

        if (((*it1).get_coef() < 0.002) && ((*it1).get_coef() > -0.002)) {
            flag = true;
            it3 = it1;
            continue;
        }

        List<Monom>::iterator it2 = it1;
        for (++it2; it2 != polynom.end(); ++it2) {
            if ((*it2).get_deg() == (*it1).get_deg()) {
                (*it2) += (*it1);
                if ((*it1).get_coef() == -(*it2).get_coef()) {
                    polynom.erase(it2);
                }
                it3 = it1;
                flag = true;
                break;
            }
        }
    }

    if (flag) {
        polynom.erase(it3);
        flag = false;
    }

    if (polynom.get_size() == 0)
        polynom.add({ 0,0 });
}

Polynom  Polynom::integral(char param)
{
    Polynom tmp;
    Monom tp;
    for (List<Monom>::iterator it = polynom.begin();
        it != polynom.end(); ++it)
    {
        tp = *it;
        tp.integral(param);
        if (tp.integral(param).get_coef() != 0)
        tmp.add_monom(tp.integral(param));
    }
    return tmp;
}

Polynom  Polynom::derivative(char param)
{
    Polynom tmp;
    Monom tp;
    for (List<Monom>::iterator it = polynom.begin();
        it != polynom.end(); ++it)
    {
        tp = *it;
        tp.derivative(param);
        if (tp.derivative(param).get_coef()!=0)
        tmp.add_monom(tp.derivative(param));
    }
    return tmp;
}

Polynom& Polynom::operator+=(const Polynom& other)
{
    List<Monom>::iterator iter_lhs = polynom.begin();
    List<Monom>::iterator iter_rhs = other.polynom.begin();
    while (iter_rhs != other.polynom.end()) {
        polynom.add(*iter_rhs);
        ++iter_rhs;
    }
    polynom = sort(*this).polynom;
    this->optimize_polynom();
    return *this;
}

Polynom& Polynom::operator-=(const Polynom& other)
{
    List<Monom>::iterator iter_lhs = polynom.begin();
    List<Monom>::iterator iter_rhs = other.polynom.begin();
    while (iter_rhs != other.polynom.end()) {
        polynom.add((*iter_rhs) * (-1));
        ++iter_rhs;
    }
    polynom = sort(*this).polynom;
    this->optimize_polynom();
    return *this;
}

Polynom& Polynom::operator*=(const double num)
{
    for (List<Monom>::iterator it = polynom.begin(); it != polynom.end(); ++it) {
        *it *= num;
    }
    return *this;
}

Polynom& Polynom::operator*=(const Polynom& other)
{
    Polynom out;
    List<Monom>::iterator iter_lhs = polynom.begin();
    List<Monom>::iterator iter_rhs = other.polynom.begin();
    while (iter_rhs != other.polynom.end()) {
        iter_lhs = polynom.begin();
        while (iter_lhs != polynom.end()) {
            out.polynom.add(*iter_rhs * *iter_lhs);
            ++iter_lhs;
        }
        ++iter_rhs;
    }
    std::swap(*this, out);
    this->optimize_polynom();
    return *this;
}

bool operator==(const Polynom& rhs, const Polynom& lhs)
{
    if (rhs.polynom.get_size() != lhs.polynom.get_size())
        return false;
    List<Monom>::iterator iter_lhs = rhs.polynom.begin();
    List<Monom>::iterator iter_rhs = lhs.polynom.begin();
    for (; iter_lhs != lhs.polynom.end() || iter_rhs != rhs.polynom.end(); ++iter_lhs, ++iter_rhs) {
        if (((*iter_lhs).get_deg()) != ((*iter_rhs).get_deg())) {
            return false;
        }
        if ((*iter_lhs).get_coef() != (*iter_rhs).get_coef()) {
            return false;
        }
    }
    return true;
} 

Polynom operator+(const Polynom& lhs, const Polynom& rhs)
{
    Polynom temp(lhs);
    return temp += rhs;
}

Polynom operator-(const Polynom& lhs, const Polynom& rhs)
{
    Polynom temp(lhs);
    return temp -= rhs;
}

Polynom operator*(const Polynom& lhs, const Polynom& rhs)
{
    Polynom temp(lhs);
    return temp *= rhs;
}

Polynom operator*(const Polynom& lhs, double num)
{
    Polynom temp(lhs);
    return temp *= num;
}

Polynom operator*(double num, const Polynom& rhs)
{
    Polynom temp(rhs);
    return temp *= num;
}

void Polynom::write_to_file(std::string path) const
{
    std::ofstream out;
    out.open(path);
    if (!out.is_open())
        throw EqException(error_codes::k_FILE_SYSTEM_ERROR);
    operator<<(out, *this);
    out.close();
}

void Polynom::read_from_file(std::string path)
{
    std::ifstream in;
    in.open(path);
    if (!in.is_open())
        throw EqException(error_codes::k_FILE_SYSTEM_ERROR);
    operator>>(in, *this);
    in.close();
}

double Polynom::calculate_in_point(double x, double y, double z)
{
    if (polynom.get_size() == 0) {
        throw EqException(error_codes::k_CALCULATE_EMPTY_EXPRESSION);
    }

    int a, b, c;
    double result = 0;
    for (List<Monom>::iterator it = polynom.begin(); it != polynom.end(); ++it) {
        c = (*it).get_deg() % BASE;
        b = (((*it).get_deg() - c) / BASE) % BASE;
        a = ((((*it).get_deg() - b - c) / BASE) / BASE);
        result += (*it).get_deg() * pow(x, a) * pow(y, b) * pow(z, c);
    }
    return result;
}