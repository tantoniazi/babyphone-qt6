#ifndef CONTACT_H
#define CONTACT_H

#include <QString>

class Contact
{
public:
    Contact() = default;

    QString itsPhoneNumber;
    QString itsName;

    bool HasValidNumber() const {
        return !itsPhoneNumber.isEmpty() && itsPhoneNumber.length() >= 6;
    }

    QString GetDisplayString() const {
        if (!itsName.isEmpty())
            return itsName + " (" + itsPhoneNumber + ")";
        return itsPhoneNumber;
    }

    void SetNumber(const QString &number) {
        itsPhoneNumber = number;
    }

    bool IsNumberMatching(const QString &number) const {
        return itsPhoneNumber == number;
    }
};

#endif // CONTACT_H
