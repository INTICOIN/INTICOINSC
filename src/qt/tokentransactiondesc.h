#ifndef QTUM_QT_TOKENTRANSACTIONDESC_H
#define QTUM_QT_TOKENTRANSACTIONDESC_H

#include <QObject>
#include <QString>

class TokenTransactionRecord;

namespace interfaces {
class Wallet;
struct TokenTx;
}

/** Provide a human-readable extended INTI description of a token transaction.
 */
class TokenTransactionDesc: public QObject
{
    Q_OBJECT

public:
    static QString toINTI(interfaces::Wallet& wallet, interfaces::TokenTx& wtx, TokenTransactionRecord *rec);

private:
    TokenTransactionDesc() {}

    static QString FormatTxStatus(interfaces::Wallet& wallet, const interfaces::TokenTx& wtx);
};

#endif // QTUM_QT_TOKENTRANSACTIONDESC_H
