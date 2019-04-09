%%------------------------------------------------------------
%%
%% Implementation stub file
%% 
%% Target: CosTransactions_TransIdentity
%% Source: /net/isildur/ldisk/daily_build/r16b02_prebuild_opu_o.2013-09-16_20/otp_src_R16B02/lib/cosTransactions/src/CosTransactions.idl
%% IC vsn: 4.3.3
%% 
%% This file is automatically generated. DO NOT EDIT IT.
%%
%%------------------------------------------------------------

-module('CosTransactions_TransIdentity').
-ic_compiled("4_3_3").


-include("CosTransactions.hrl").

-export([tc/0,id/0,name/0]).



%% returns type code
tc() -> {tk_struct,"IDL:omg.org/CosTransactions/TransIdentity:1.0",
                   "TransIdentity",
                   [{"coord",
                     {tk_objref,"IDL:omg.org/CosTransactions/Coordinator:1.0",
                                "Coordinator"}},
                    {"term",
                     {tk_objref,"IDL:omg.org/CosTransactions/Terminator:1.0",
                                "Terminator"}},
                    {"otid",
                     {tk_struct,"IDL:omg.org/CosTransactions/otid_t:1.0",
                                "otid_t",
                                [{"formatID",tk_long},
                                 {"bqual_length",tk_long},
                                 {"tid",{tk_sequence,tk_octet,0}}]}}]}.

%% returns id
id() -> "IDL:omg.org/CosTransactions/TransIdentity:1.0".

%% returns name
name() -> "CosTransactions_TransIdentity".



