#include "uritests.h"
#include "../guiutil.h"
#include "../walletmodel.h"

#include <QUrl>

void URITests::uriTests()
{
    SendCoinsRecipient rv;
    QUrl uri;
    uri.setUrl(QString("bitshares-pts:Pdpfdm37p5Ps9k24jyhxZwwNmiXQA3sgoE?req-dontexist="));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("bitshares-pts:Pdpfdm37p5Ps9k24jyhxZwwNmiXQA3sgoE?dontexist="));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("Pdpfdm37p5Ps9k24jyhxZwwNmiXQA3sgoE"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 0);

    uri.setUrl(QString("bitshares-pts:Pdpfdm37p5Ps9k24jyhxZwwNmiXQA3sgoE?label=Wikipedia Example Address"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("Pdpfdm37p5Ps9k24jyhxZwwNmiXQA3sgoE"));
    QVERIFY(rv.label == QString("Wikipedia Example Address"));
    QVERIFY(rv.amount == 0);

    uri.setUrl(QString("bitshares-pts:Pdpfdm37p5Ps9k24jyhxZwwNmiXQA3sgoE?amount=0.001"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("Pdpfdm37p5Ps9k24jyhxZwwNmiXQA3sgoE"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 100000);

    uri.setUrl(QString("bitshares-pts:Pdpfdm37p5Ps9k24jyhxZwwNmiXQA3sgoE?amount=1.001"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("Pdpfdm37p5Ps9k24jyhxZwwNmiXQA3sgoE"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 100100000);

    uri.setUrl(QString("bitshares-pts:Pdpfdm37p5Ps9k24jyhxZwwNmiXQA3sgoE?amount=100&label=Wikipedia Example"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("Pdpfdm37p5Ps9k24jyhxZwwNmiXQA3sgoE"));
    QVERIFY(rv.amount == 10000000000LL);
    QVERIFY(rv.label == QString("Wikipedia Example"));

    uri.setUrl(QString("bitshares-pts:Pdpfdm37p5Ps9k24jyhxZwwNmiXQA3sgoE?message=Wikipedia Example Address"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("Pdpfdm37p5Ps9k24jyhxZwwNmiXQA3sgoE"));
    QVERIFY(rv.label == QString());

    QVERIFY(GUIUtil::parseBitcoinURI("bitshares-pts://Pdpfdm37p5Ps9k24jyhxZwwNmiXQA3sgoE?message=Wikipedia Example Address", &rv));
    QVERIFY(rv.address == QString("Pdpfdm37p5Ps9k24jyhxZwwNmiXQA3sgoE"));
    QVERIFY(rv.label == QString());

    // We currently don't implement the message parameter (ok, yea, we break spec...)
    uri.setUrl(QString("bitshares-pts:Pdpfdm37p5Ps9k24jyhxZwwNmiXQA3sgoE?req-message=Wikipedia Example Address"));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("bitshares-pts:Pdpfdm37p5Ps9k24jyhxZwwNmiXQA3sgoE?amount=1,000&label=Wikipedia Example"));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("bitshares-pts:Pdpfdm37p5Ps9k24jyhxZwwNmiXQA3sgoE?amount=1,000.0&label=Wikipedia Example"));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));
}
