%%------------------------------------------------------------
%%
%% Implementation stub file
%% 
%% Target: CosNotification_PropertyRange
%% Source: /net/isildur/ldisk/daily_build/r16b02_prebuild_opu_o.2013-09-16_20/otp_src_R16B02/lib/cosNotification/src/CosNotification.idl
%% IC vsn: 4.3.3
%% 
%% This file is automatically generated. DO NOT EDIT IT.
%%
%%------------------------------------------------------------

-module('CosNotification_PropertyRange').
-ic_compiled("4_3_3").


-include("CosNotification.hrl").

-export([tc/0,id/0,name/0]).



%% returns type code
tc() -> {tk_struct,"IDL:omg.org/CosNotification/PropertyRange:1.0",
                   "PropertyRange",
                   [{"low_val",tk_any},{"high_val",tk_any}]}.

%% returns id
id() -> "IDL:omg.org/CosNotification/PropertyRange:1.0".

%% returns name
name() -> "CosNotification_PropertyRange".



