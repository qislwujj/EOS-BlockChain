#include <eosio/eosio.hpp>

using namespace std;
using namespace eosio;


CONTRACT addressbook2: public contract {
public:
using contract::contract;


ACTION findage(uint64_t age){
    address_index addresses(get_self(),get_self().value);
    auto forSecondary = addresses.get_index<"byage"_n>();
    auto itr = forSecondary.require_find(age,"no age");

    print(itr->user," ",itr->age);
}



ACTION upsert(name user,std::string first_name, std::string last_name, uint64_t age) {
    require_auth(user);
    address_index forUpsert(get_self(),get_self().value);
    auto itr = forUpsert.find(user.value);

    if(itr == forUpsert.end()){
        forUpsert.emplace(user, [&](auto& row) {
            row.user = user;
            row.first_name = first_name;
            row.last_name = last_name;
            row.age = age;
            });

            print("emplace success");
            send_summary(user, " successfully emplaced record to addressbook");
    }
    else{
        forUpsert.modify(itr,user, [&](auto& row) {
            row.user = user;
            row.first_name = first_name;
            row.last_name = last_name;
            row.age = age;
            });

            print("modify success");
            send_summary(user, " successfully modified record to addressbook");
    }

}



ACTION insert(name user, std::string first_name, std::string last_name, uint64_t age) {
    require_auth(user);

    address_index forInsert(get_self(), get_self().value);
    auto itr = forInsert.find(user.value);

        check(itr == forInsert.end(), "already exists");

        forInsert.emplace(user, [&](auto& row) {
        row.user = user;
        row.first_name = first_name;
        row.last_name = last_name;
        row.age = age;
    });

    print("insert success");
    send_summary(user, " successfully emplaced record to addressbook");
}


ACTION erase(name user) {
    require_auth(user);

    address_index forErase(get_self(), get_self().value);
    auto itr = forErase.require_find(user.value, "no account");
    forErase.erase(itr);

    print("erase success");
    send_summary(user, " successfully erased record from addressbook");
}

[[eosio::action]]
void notify(name user,string msg){
    require_auth(get_self());
    require_recipient(user);
}


private:
struct [[eosio::table]] person {
    name user;
    std::string first_name;
    string last_name;
    uint64_t age;

    uint64_t primary_key() const { return user.value; }
    uint64_t by_age() const{return age; }
};

void send_summary(name user,string message){
    action(
        permission_level{get_self(),"active"_n},
        get_self(),
        "notify"_n,
        make_tuple(user,name{user}.to_string()+message)
    ).send();
};

typedef multi_index<"peopletwo"_n, person, indexed_by<"byage"_n,const_mem_fun<person,uint64_t,&person::by_age>> > address_index;
};