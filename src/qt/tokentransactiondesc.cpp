#include <qt/tokentransactiondesc.h>
#include <qt/tokentransactionrecord.h>
#include <qt/bitcoinunits.h>
#include <qt/guiutil.h>
#include <qt/styleSheet.h>
#include <uint256.h>
#include <validation.h>
#include <wallet/wallet.h>
#include <timedata.h>
#include <interfaces/wallet.h>
#include <consensus/params.h>
#include <qt/guiconstants.h>

class TokenTransactionFormater
{
public:
    TokenTransactionFormater()
    {
        itemNameColor = GetStringStyleValue("tokentransactiondesc/item-name-color", "#ffffff");
        itemColor = GetStringStyleValue("tokentransactiondesc/item-color", "#ffffff");
        itemFontBold = GetIntStyleValue("tokentransactiondesc/item-font-bold", true);
        network = Params().NetworkIDString();
    }

    static const TokenTransactionFormater& instance()
    {
        static TokenTransactionFormater data;
        return data;
    }

    static QString ItemColor()
    {
        return " color='" + instance().itemColor + "'";
    }

    static QString ItemNameColor(const QString& name, bool space = true)
    {
        QString ret;
        if(instance().itemFontBold)
        {
            ret += "<b>";
        }

        ret += "<font color='" + instance().itemNameColor + "'>" + name +":</font>";

        if(instance().itemFontBold)
        {
            ret += "</b>";
        }

        if(space) ret += " ";

        return ret;
    }

    static QString TxIdLink(const QString& txHash)
    {
        if(instance().network == "main")
        {
            return QTUM_INFO_MAINNET.arg("tx", txHash);
        }
        else if(instance().network == "test")
        {
            return QTUM_INFO_TESTNET.arg("tx", txHash);
        }

        return txHash;
    }

private:
    QString itemNameColor;
    QString itemColor;
    bool itemFontBold;
    std::string network;
};

QString TokenTransactionDesc::FormatTxStatus(interfaces::Wallet &wallet, const interfaces::TokenTx &wtx)
{
    // Get token tx status
    int blockNumber = -1;
    bool inMempool = false;
    int numBlocks = -1;
    wallet.getTokenTxStatus(wtx.hash, blockNumber, inMempool, numBlocks);

    // Determine transaction status
    int nDepth= 0;
    if(wtx.block_number == -1)
    {
        nDepth = 0;
    }
    else
    {
        nDepth = numBlocks - wtx.block_number + 1;
    }

    if (nDepth < 0)
        return tr("conflicted with a transaction with %1 confirmations").arg(-nDepth);
    else if (nDepth == 0)
    {
        if(inMempool)
            return tr("0/unconfirmed, in memory pool");
        else
            return tr("0/unconfirmed, not in memory pool");
    }
    else if (nDepth < TokenTransactionRecord::RecommendedNumConfirmations)
        return tr("%1/unconfirmed").arg(nDepth);
    else
        return tr("%1 confirmations").arg(nDepth);
}

QString TokenTransactionDesc::toINTI(interfaces::Wallet &wallet, interfaces::TokenTx &wtx, TokenTransactionRecord *rec)
{
    QString strINTI;

    strINTI.reserve(4000);
    strINTI += "<html><font face='verdana, arial, helvetica, sans-serif'"+TokenTransactionFormater::ItemColor()+">";

    int64_t nTime = rec->time;
    dev::s256 nDebit = rec->debit;
    dev::s256 nCredit = rec->credit;
    dev::s256 nNet = nCredit + nDebit;
    QString unit = QString::fromStdString(rec->tokenSymbol);

    strINTI += TokenTransactionFormater::ItemNameColor(tr("Status")) + FormatTxStatus(wallet, wtx);

    strINTI += "<br>";

    strINTI += TokenTransactionFormater::ItemNameColor(tr("Date")) + (nTime ? GUIUtil::dateTimeStr(nTime) : "") + "<br>";

    strINTI += TokenTransactionFormater::ItemNameColor(tr("Transaction ID")) + TokenTransactionFormater::TxIdLink(rec->getTxID()) + "<br>";

    strINTI += TokenTransactionFormater::ItemNameColor(tr("Token Address")) + QString::fromStdString(wtx.contract_address) + "<br>";

    strINTI += TokenTransactionFormater::ItemNameColor(tr("From")) + QString::fromStdString(wtx.sender_address) + "<br>";

    strINTI += TokenTransactionFormater::ItemNameColor(tr("To")) + QString::fromStdString(wtx.receiver_address) + "<br>";

    if(nCredit > 0)
    {
         strINTI += TokenTransactionFormater::ItemNameColor(tr("Credit")) + BitcoinUnits::formatTokenWithUnit(unit, rec->decimals, nCredit, true) + "<br>";
    }
    if(nDebit < 0)
    {
         strINTI += TokenTransactionFormater::ItemNameColor(tr("Debit")) + BitcoinUnits::formatTokenWithUnit(unit, rec->decimals, nDebit, true) + "<br>";
    }
    strINTI += TokenTransactionFormater::ItemNameColor(tr("Net Amount")) + BitcoinUnits::formatTokenWithUnit(unit, rec->decimals, nNet, true) + "<br>";


    strINTI += "</font></html>";
    return strINTI;
}
