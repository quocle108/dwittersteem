/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once

#include <eosiolib/asset.hpp>
#include <eosiolib/eosio.hpp>

#include <string>

namespace eosiosystem {
   class system_contract;
}

namespace eosio {

   using std::string;

   class token : public contract {
      public:
         token( account_name self ):contract(self){}
	   
         //@abi action
         void check(account_name user, string memo);

	     //@abi action
         void stake(account_name from, account_name to, asset quantity);
	     //@abi action
         void unstake(account_name from,  account_name to, asset quantity);
	     //@abi action
         void update(account_name user);
	 //@abi action
         void transfer(account_name from, bool internalfrom, account_name to, bool internalto, asset balance, string memo);
	   
     

      private:

      
         //@abi table pubtbl i64
         struct pub_table {
            account_name user;
            asset balance;
	    asset ink;
	    bool is_internal;
            
            uint64_t primary_key()const {return user;}
            EOSLIB_SERIALIZE(pub_table,(user)(balance)(ink)(is_internal))
         };
	   
	   //@abi table staketbl i64
	   struct stake_table {
		   account_name user;
		   account_name owner;
		   asset balance;
		   uint32_t staked_at;
		   
		   uint64_t primary_key()const {return user;}
		   EOSLIB_SERIALIZE(stake_table,(user)(owner)(balance)(staked_at))
	   }; 
	   
	   //@abi table unstaketbl i64
	   struct unstake_table {
		   account_name user;
		   asset balance;
		   uint32_t unstaked_at;
		   
		   uint64_t primary_key()const {return user;}
		   EOSLIB_SERIALIZE(unstake_table,(user)(balance)(unstaked_at))
	   }; 
            


         typedef eosio::multi_index<N(pubtbl), pub_table> pubtbl;
	   typedef eosio::multi_index<N(staketbl), stake_table> staketbl;
	   typedef eosio::multi_index<N(unstaketbl), unstake_table> unstaketbl;

         void sub_balance( account_name owner, asset value );
         void add_balance( account_name owner, asset value, account_name ram_payer );
	   
	 //@abi action
         void save(account_name user, asset quantity);
	 //@abi action
         void draw(account_name user, asset quantity);

      public:
         struct transfer_args {
            account_name  from;
            account_name  to;
            asset         quantity;
            string        memo;
         };
   };





} /// namespace eosio
