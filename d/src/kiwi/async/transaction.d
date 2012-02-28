module kiwi.async.transaction;

import kiwi.async.proxy;

struct TransactionOutcome
{
    TransactionID id;
    bool status;
}


alias void delegate(bool) TransactionCallback;


private TransactionCallback[TransactionID] _transactionCallbacks;
private uint _nextTransactionID;

uint genTransactionID()
{
    return _nextTransactionID++;
}

void addTransactionCallback(TransactionID id, TransactionCallback callback)
{
    _transactionCallbacks[id] = callback;
}

