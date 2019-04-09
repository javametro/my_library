/*
 *  Warning: Do not edit this file.
 *  Auto-generated by 'beam_makeops'.
 */

OpCase(i_bs_get_binary2_frIsId):
    { Eterm targ1; Eterm dst; 
    BeamInstr* next;
    PreFetch(5, next);
    GetR(2, targ1);
    dst = Arg(4);
    BsGetBinary_2(r(0), Arg(1), targ1, Arg(3), dst, StoreResult, ClauseFail());
    NextPF(5, next);
    }

OpCase(i_bs_get_binary2_fxIsId):
    { Eterm targ1; Eterm dst; 
    BeamInstr* next;
    PreFetch(6, next);
    GetR(3, targ1);
    dst = Arg(5);
    BsGetBinary_2(xb(Arg(1)), Arg(2), targ1, Arg(4), dst, StoreResult, ClauseFail());
    NextPF(6, next);
    }

OpCase(i_bs_get_binary_all2_frIId):
    { Eterm dst; 
    BeamInstr* next;
    PreFetch(4, next);
    dst = Arg(3);
    BsGetBinaryAll_2(r(0), Arg(1), Arg(2), dst, StoreResult, ClauseFail());
    NextPF(4, next);
    }

OpCase(i_bs_get_binary_all2_fxIId):
    { Eterm dst; 
    BeamInstr* next;
    PreFetch(5, next);
    dst = Arg(4);
    BsGetBinaryAll_2(xb(Arg(1)), Arg(2), Arg(3), dst, StoreResult, ClauseFail());
    NextPF(5, next);
    }

OpCase(i_bs_get_binary_imm2_frIIId):
    { Eterm dst; 
    BeamInstr* next;
    PreFetch(5, next);
    dst = Arg(4);
    BsGetBinaryImm_2(r(0), Arg(1), Arg(2), Arg(3), dst, StoreResult, ClauseFail());
    NextPF(5, next);
    }

OpCase(i_bs_get_binary_imm2_fxIIId):
    { Eterm dst; 
    BeamInstr* next;
    PreFetch(6, next);
    dst = Arg(5);
    BsGetBinaryImm_2(xb(Arg(1)), Arg(2), Arg(3), Arg(4), dst, StoreResult, ClauseFail());
    NextPF(6, next);
    }

OpCase(i_bs_get_float2_frIsId):
    { Eterm targ1; Eterm dst; 
    BeamInstr* next;
    PreFetch(5, next);
    GetR(2, targ1);
    dst = Arg(4);
    BsGetFloat2(r(0), Arg(1), targ1, Arg(3), dst, StoreResult, ClauseFail());
    NextPF(5, next);
    }

OpCase(i_bs_get_float2_fxIsId):
    { Eterm targ1; Eterm dst; 
    BeamInstr* next;
    PreFetch(6, next);
    GetR(3, targ1);
    dst = Arg(5);
    BsGetFloat2(xb(Arg(1)), Arg(2), targ1, Arg(4), dst, StoreResult, ClauseFail());
    NextPF(6, next);
    }

OpCase(i_bs_skip_bits2_frxI):
    { 
    BeamInstr* next;
    PreFetch(3, next);
    BsSkipBits2(r(0), xb(Arg(1)), Arg(2), ClauseFail());
    NextPF(3, next);
    }

OpCase(i_bs_skip_bits2_fryI):
    { 
    BeamInstr* next;
    PreFetch(3, next);
    BsSkipBits2(r(0), yb(Arg(1)), Arg(2), ClauseFail());
    NextPF(3, next);
    }

OpCase(i_bs_skip_bits2_fxrI):
    { 
    BeamInstr* next;
    PreFetch(3, next);
    BsSkipBits2(xb(Arg(1)), r(0), Arg(2), ClauseFail());
    NextPF(3, next);
    }

OpCase(i_bs_skip_bits2_fxxI):
    { 
    BeamInstr* next;
    PreFetch(4, next);
    BsSkipBits2(xb(Arg(1)), xb(Arg(2)), Arg(3), ClauseFail());
    NextPF(4, next);
    }

OpCase(i_bs_skip_bits2_fxyI):
    { 
    BeamInstr* next;
    PreFetch(4, next);
    BsSkipBits2(xb(Arg(1)), yb(Arg(2)), Arg(3), ClauseFail());
    NextPF(4, next);
    }

OpCase(i_bs_skip_bits_all2_frI):
    { 
    BeamInstr* next;
    PreFetch(2, next);
    BsSkipBitsAll2(r(0), Arg(1), ClauseFail());
    NextPF(2, next);
    }

OpCase(i_bs_skip_bits_all2_fxI):
    { 
    BeamInstr* next;
    PreFetch(3, next);
    BsSkipBitsAll2(xb(Arg(1)), Arg(2), ClauseFail());
    NextPF(3, next);
    }

OpCase(i_bs_skip_bits_imm2_frI):
    { 
    BeamInstr* next;
    PreFetch(2, next);
    BsSkipBitsImm2(r(0), Arg(1), ClauseFail());
    NextPF(2, next);
    }

OpCase(i_bs_skip_bits_imm2_fxI):
    { 
    BeamInstr* next;
    PreFetch(3, next);
    BsSkipBitsImm2(xb(Arg(1)), Arg(2), ClauseFail());
    NextPF(3, next);
    }

OpCase(i_fetch_ss):
    { Eterm targ1; Eterm targ2; 
    BeamInstr* next;
    PreFetch(2, next);
    GetR(0, targ1);
    GetR(1, targ2);
    FetchArgs(targ1, targ2);
    NextPF(2, next);
    }

OpCase(i_get_tuple_element_rPr):
    { 
    BeamInstr* next;
    PreFetch(1, next);
    GetTupleElement(r(0), Arg(0), r(0));
    NextPF(1, next);
    }

OpCase(i_get_tuple_element_rPy):
    { 
    BeamInstr* next;
    PreFetch(2, next);
    GetTupleElement(r(0), Arg(0), yb(Arg(1)));
    NextPF(2, next);
    }

OpCase(i_get_tuple_element_xPy):
    { 
    BeamInstr* next;
    PreFetch(3, next);
    GetTupleElement(xb(Arg(0)), Arg(1), yb(Arg(2)));
    NextPF(3, next);
    }

OpCase(i_get_tuple_element_yPy):
    { 
    BeamInstr* next;
    PreFetch(3, next);
    GetTupleElement(yb(Arg(0)), Arg(1), yb(Arg(2)));
    NextPF(3, next);
    }

OpCase(i_make_fun_It):
    { 
    BeamInstr* next;
    PreFetch(2, next);
    MakeFun(Arg(0), Arg(1));
    NextPF(2, next);
    }

OpCase(i_new_bs_put_binary_all_jsI):
    { Eterm targ1; 
    BeamInstr* next;
    PreFetch(3, next);
    GetR(1, targ1);
    NewBsPutBinaryAll(targ1, Arg(2));
    NextPF(3, next);
    }

OpCase(i_new_bs_put_binary_imm_jIs):
    { Eterm targ1; 
    BeamInstr* next;
    PreFetch(3, next);
    GetR(2, targ1);
    NewBsPutBinaryImm(Arg(1), targ1);
    NextPF(3, next);
    }

OpCase(i_new_bs_put_binary_jsIs):
    { Eterm targ1; Eterm targ2; 
    BeamInstr* next;
    PreFetch(4, next);
    GetR(1, targ1);
    GetR(3, targ2);
    NewBsPutBinary(targ1, Arg(2), targ2);
    NextPF(4, next);
    }

OpCase(i_new_bs_put_float_imm_jIIs):
    { Eterm targ1; 
    BeamInstr* next;
    PreFetch(4, next);
    GetR(3, targ1);
    NewBsPutFloatImm(Arg(1), Arg(2), targ1);
    NextPF(4, next);
    }

OpCase(i_new_bs_put_float_jsIs):
    { Eterm targ1; Eterm targ2; 
    BeamInstr* next;
    PreFetch(4, next);
    GetR(1, targ1);
    GetR(3, targ2);
    NewBsPutFloat(targ1, Arg(2), targ2);
    NextPF(4, next);
    }

OpCase(i_new_bs_put_integer_imm_jIIs):
    { Eterm targ1; 
    BeamInstr* next;
    PreFetch(4, next);
    GetR(3, targ1);
    NewBsPutIntegerImm(Arg(1), Arg(2), targ1);
    NextPF(4, next);
    }

OpCase(i_new_bs_put_integer_jsIs):
    { Eterm targ1; Eterm targ2; 
    BeamInstr* next;
    PreFetch(4, next);
    GetR(1, targ1);
    GetR(3, targ2);
    NewBsPutInteger(targ1, Arg(2), targ2);
    NextPF(4, next);
    }

OpCase(is_atom_fy):
    { 
    BeamInstr* next;
    PreFetch(2, next);
    IsAtom(yb(Arg(1)), ClauseFail());
    NextPF(2, next);
    }

OpCase(is_binary_fy):
    { 
    BeamInstr* next;
    PreFetch(2, next);
    IsBinary(yb(Arg(1)), ClauseFail());
    NextPF(2, next);
    }

OpCase(is_bitstring_fy):
    { 
    BeamInstr* next;
    PreFetch(2, next);
    IsBitstring(yb(Arg(1)), ClauseFail());
    NextPF(2, next);
    }

OpCase(is_boolean_fr):
    { 
    BeamInstr* next;
    PreFetch(1, next);
    IsBoolean(r(0), ClauseFail());
    NextPF(1, next);
    }

OpCase(is_boolean_fx):
    { 
    BeamInstr* next;
    PreFetch(2, next);
    IsBoolean(xb(Arg(1)), ClauseFail());
    NextPF(2, next);
    }

OpCase(is_boolean_fy):
    { 
    BeamInstr* next;
    PreFetch(2, next);
    IsBoolean(yb(Arg(1)), ClauseFail());
    NextPF(2, next);
    }

OpCase(is_float_fy):
    { 
    BeamInstr* next;
    PreFetch(2, next);
    IsFloat(yb(Arg(1)), ClauseFail());
    NextPF(2, next);
    }

OpCase(is_list_fy):
    { 
    BeamInstr* next;
    PreFetch(2, next);
    IsList(yb(Arg(1)), ClauseFail());
    NextPF(2, next);
    }

OpCase(is_number_fr):
    { 
    BeamInstr* next;
    PreFetch(1, next);
    IsNumber(r(0), ClauseFail());
    NextPF(1, next);
    }

OpCase(is_number_fx):
    { 
    BeamInstr* next;
    PreFetch(2, next);
    IsNumber(xb(Arg(1)), ClauseFail());
    NextPF(2, next);
    }

OpCase(is_number_fy):
    { 
    BeamInstr* next;
    PreFetch(2, next);
    IsNumber(yb(Arg(1)), ClauseFail());
    NextPF(2, next);
    }

OpCase(is_pid_fy):
    { 
    BeamInstr* next;
    PreFetch(2, next);
    IsPid(yb(Arg(1)), ClauseFail());
    NextPF(2, next);
    }

OpCase(is_port_fy):
    { 
    BeamInstr* next;
    PreFetch(2, next);
    IsPort(yb(Arg(1)), ClauseFail());
    NextPF(2, next);
    }

OpCase(is_reference_fy):
    { 
    BeamInstr* next;
    PreFetch(2, next);
    IsRef(yb(Arg(1)), ClauseFail());
    NextPF(2, next);
    }

OpCase(node_y):
    { 
    BeamInstr* next;
    PreFetch(1, next);
    Node(yb(Arg(0)));
    NextPF(1, next);
    }

OpCase(put_list_ssd):
    { Eterm targ1; Eterm targ2; Eterm dst; 
    BeamInstr* next;
    PreFetch(3, next);
    GetR(0, targ1);
    GetR(1, targ2);
    dst = Arg(2);
    PutList(targ1, targ2, dst, StoreResult);
    NextPF(3, next);
    }

