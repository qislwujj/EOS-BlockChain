#include <eosio/eosio.hpp> 
#include <eosio/asset.hpp>
//각 테이블에 name type변수를 선언  => EOS를 보낸사람 || EOS를 받은사람 그리고 얼마나 받았는지 기록
using namespace eosio;


CONTRACT onnotify2: public contract {
    public:

    using contract::contract;


    ACTION dummy() {}


    [[eosio::on_notify("eosio.token::transfer")]]

    void ontransfer(name from, name to, asset quantity, std::string memo) {

        if(from == get_self()) {
            Receive forReceiver(get_self(), get_self().value);
            forReceiver.emplace(get_self(), [&](auto& row) {
            row.mykey = forReceiver.available_primary_key();
            row.user = to;
            row.balance = quantity;
            });
        }
        else {
            Send forSender(get_self(), get_self().value);
            forSender.emplace(get_self(), [&](auto& row) {
            row.mykey = forSender.available_primary_key();
            row.user = from;
            row.balance = quantity;
            });
        }
    }
    
        private:
        TABLE tradingbook_struct {
            uint64_t mykey;
            name user;
            asset balance;
            uint64_t primary_key() const { return mykey; }
        };
        
    typedef multi_index<"senderbook"_n, tradingbook_struct> Send;
    typedef multi_index<"receiverbook"_n, tradingbook_struct> Receive;
};