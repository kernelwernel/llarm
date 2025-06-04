; ModuleID = '/tmp/autogen.bc'
source_filename = "/tmp/autogen.bc"

define void @autogen_SD0(ptr %0, ptr %1, ptr %2, i32 %3, i64 %4, i8 %5) {
BB:
  %A4 = alloca <4 x i16>, align 8
  %A3 = alloca <4 x i64>, align 32
  %A2 = alloca <2 x float>, align 8
  %A1 = alloca <8 x i16>, align 16
  %A = alloca <4 x i32>, align 16
  %L = load <2 x i16>, ptr %A, align 4
  store i32 0, ptr %0, align 4
  %E = extractelement <1 x i32> zeroinitializer, i32 32529
  %Shuff = shufflevector <1 x i32> zeroinitializer, <1 x i32> zeroinitializer, <1 x i32> poison
  %I = insertelement <2 x i32> zeroinitializer, i32 0, i32 132849
  %B = udiv <4 x i8> zeroinitializer, zeroinitializer
  %Se = sext i8 77 to i16
  %Sl = select <16 x i1> <i1 true, i1 false, i1 true, i1 false, i1 true, i1 false, i1 true, i1 false, i1 true, i1 false, i1 true, i1 false, i1 true, i1 false, i1 true, i1 false>, <16 x i64> zeroinitializer, <16 x i64> zeroinitializer
  %L5 = load i8, ptr %0, align 1
  store <16 x double> <double 0.000000e+00, double 0xFFFFFFFFFFFFFFFF, double 0.000000e+00, double 0xFFFFFFFFFFFFFFFF, double 0.000000e+00, double 0xFFFFFFFFFFFFFFFF, double 0.000000e+00, double 0xFFFFFFFFFFFFFFFF, double 0.000000e+00, double 0xFFFFFFFFFFFFFFFF, double 0.000000e+00, double 0xFFFFFFFFFFFFFFFF, double 0.000000e+00, double 0xFFFFFFFFFFFFFFFF, double 0.000000e+00, double 0xFFFFFFFFFFFFFFFF>, ptr %A2, align 128
  %E6 = extractelement <16 x i64> %Sl, i32 132849
  %Shuff7 = shufflevector <16 x i64> zeroinitializer, <16 x i64> zeroinitializer, <16 x i32> <i32 2, i32 4, i32 6, i32 8, i32 10, i32 12, i32 14, i32 16, i32 18, i32 20, i32 22, i32 24, i32 26, i32 poison, i32 30, i32 0>
  %I8 = insertelement <4 x i8> zeroinitializer, i8 21, i32 %3
  %B9 = xor i64 251161, 251161
  %Tr = trunc <4 x i8> %B to <4 x i1>
  %Sl10 = select i1 true, <4 x i32> zeroinitializer, <4 x i32> zeroinitializer
  %Cmp = icmp ult <1 x i32> %Shuff, %Shuff
  %L11 = load i64, ptr %0, align 4
  store <4 x double> <double 0.000000e+00, double 0xFFFFFFFFFFFFFFFF, double 0.000000e+00, double 0xFFFFFFFFFFFFFFFF>, ptr %0, align 32
  %E12 = extractelement <1 x i32> zeroinitializer, i32 32529
  %Shuff13 = shufflevector <16 x i64> zeroinitializer, <16 x i64> zeroinitializer, <16 x i32> <i32 4, i32 6, i32 poison, i32 10, i32 12, i32 14, i32 16, i32 poison, i32 20, i32 22, i32 24, i32 26, i32 28, i32 30, i32 0, i32 2>
  %I14 = insertelement <1 x i32> %Shuff, i32 %E12, i32 132849
  %B15 = add i64 %4, %L11
  %FC = uitofp <4 x i64> zeroinitializer to <4 x float>
  %Sl16 = select i1 true, ptr %A4, ptr %0
  %Cmp17 = icmp ne <4 x i8> %B, %B
  %L18 = load i32, ptr %Sl16, align 4
  store <4 x i8> %B, ptr %Sl16, align 4
  %E19 = extractelement <16 x i64> %Sl, i32 %E
  %Shuff20 = shufflevector <4 x i8> %B, <4 x i8> %I8, <4 x i32> poison
  %I21 = insertelement <4 x i8> %B, i8 21, i32 %L18
  %B22 = fadd float 0xC4F0BB4480000000, 0xC4F0BB4480000000
  %PC = bitcast ptr %A2 to ptr
  %Sl23 = select i1 true, <1 x i32> zeroinitializer, <1 x i32> %Shuff
  %Cmp24 = icmp ugt i64 %E19, 251161
  br label %CF85

CF85:                                             ; preds = %BB
  %L25 = load i64, ptr %A3, align 4
  store <8 x i64> <i64 0, i64 -1, i64 0, i64 -1, i64 0, i64 -1, i64 0, i64 -1>, ptr %Sl16, align 64
  %E26 = extractelement <4 x i8> %I8, i32 %E12
  %Shuff27 = shufflevector <16 x i16> zeroinitializer, <16 x i16> zeroinitializer, <16 x i32> <i32 14, i32 poison, i32 18, i32 20, i32 22, i32 poison, i32 26, i32 28, i32 30, i32 0, i32 2, i32 poison, i32 poison, i32 8, i32 10, i32 12>
  %I28 = insertelement <16 x i16> zeroinitializer, i16 18437, i32 %E
  %B29 = xor i16 -2255, 18437
  %PC30 = bitcast ptr %0 to ptr
  %Sl31 = select i1 true, i8 77, i8 21
  %Cmp32 = fcmp ord double 0x18DF23FE11DD527C, 0xAE97BFB633957A34
  br label %CF

CF:                                               ; preds = %CF, %CF84, %CF86, %CF85
  %L33 = load <8 x i16>, ptr %Sl16, align 16
  store i64 251161, ptr %A3, align 4
  %E34 = extractelement <8 x i16> %L33, i32 %L18
  %Shuff35 = shufflevector <4 x i8> %I8, <4 x i8> %B, <4 x i32> <i32 1, i32 3, i32 5, i32 7>
  %I36 = insertelement <16 x i64> %Shuff7, i64 251161, i32 %3
  %B37 = shl <4 x i8> %I8, zeroinitializer
  %Tr38 = trunc <16 x i64> zeroinitializer to <16 x i32>
  %Sl39 = select <4 x i1> %Tr, <4 x i8> %I8, <4 x i8> zeroinitializer
  %Cmp40 = icmp slt i16 %B29, 18437
  br i1 %Cmp40, label %CF, label %CF82

CF82:                                             ; preds = %CF82, %CF
  %L41 = load <8 x i32>, ptr %PC30, align 32
  store i64 251161, ptr %Sl16, align 4
  %E42 = extractelement <16 x i64> zeroinitializer, i32 %3
  %Shuff43 = shufflevector <4 x i8> zeroinitializer, <4 x i8> %B, <4 x i32> <i32 poison, i32 1, i32 poison, i32 5>
  %I44 = insertelement <16 x i64> %Shuff13, i64 251161, i32 32529
  %B45 = xor i32 132849, %3
  %FC46 = uitofp i16 %Se to double
  %Sl47 = select i1 %Cmp32, i1 %Cmp40, i1 %Cmp24
  br i1 %Sl47, label %CF82, label %CF83

CF83:                                             ; preds = %CF83, %CF82
  %Cmp48 = fcmp oeq <4 x float> %FC, %FC
  %L49 = load i32, ptr %Sl16, align 4
  store <8 x i32> %L41, ptr %A4, align 32
  %E50 = extractelement <4 x i8> %Shuff43, i32 32529
  %Shuff51 = shufflevector <4 x i1> %Cmp48, <4 x i1> %Tr, <4 x i32> <i32 4, i32 6, i32 0, i32 2>
  %I52 = insertelement <4 x i8> %Shuff35, i8 21, i32 %E12
  %B53 = urem <2 x i32> %I, zeroinitializer
  %FC54 = uitofp <16 x i16> %I28 to <16 x double>
  %Sl55 = select i1 %Cmp40, i64 %4, i64 %E19
  %Cmp56 = icmp ugt i64 %E6, %E6
  br i1 %Cmp56, label %CF83, label %CF84

CF84:                                             ; preds = %CF83
  %L57 = load double, ptr %PC30, align 8
  %E58 = extractelement <16 x i16> zeroinitializer, i32 132849
  %Shuff59 = shufflevector <1 x i32> zeroinitializer, <1 x i32> %Shuff, <1 x i32> <i32 1>
  %I60 = insertelement <4 x i8> %Shuff20, i8 %E26, i32 %B45
  %B61 = udiv <4 x i8> %I8, %Shuff43
  %Tr62 = trunc <1 x i32> %Sl23 to <1 x i8>
  %Sl63 = select <4 x i1> %Cmp48, <4 x i8> %B61, <4 x i8> %B
  %Cmp64 = icmp ule i16 %Se, -2255
  br i1 %Cmp64, label %CF, label %CF81

CF81:                                             ; preds = %CF81, %CF84
  %L65 = load <16 x double>, ptr %Sl16, align 128
  store float 0xC4F0BB4480000000, ptr %Sl16, align 4
  %E66 = extractelement <4 x i8> %Sl39, i32 %B45
  %Shuff67 = shufflevector <4 x float> %FC, <4 x float> %FC, <4 x i32> <i32 1, i32 3, i32 5, i32 poison>
  %I68 = insertelement <4 x i8> %Sl63, i8 21, i32 %B45
  %B69 = and i16 18761, 16293
  %PC70 = bitcast ptr %A1 to ptr
  %Sl71 = select i1 %Cmp24, i32 %E, i32 %B45
  %Cmp72 = icmp ult i16 %E34, %Se
  br i1 %Cmp72, label %CF81, label %CF86

CF86:                                             ; preds = %CF81
  %L73 = load i32, ptr %Sl16, align 4
  store <8 x i16> %L33, ptr %PC30, align 16
  %E74 = extractelement <4 x i8> %Shuff35, i32 %E12
  %Shuff75 = shufflevector <1 x i32> %Shuff59, <1 x i32> %Shuff, <1 x i32> zeroinitializer
  %I76 = insertelement <8 x i16> %L33, i16 %E58, i32 %Sl71
  %Tr77 = trunc <4 x i8> %Shuff20 to <4 x i1>
  %Sl78 = select i1 %Cmp40, i64 %B15, i64 %E6
  %Cmp79 = icmp ult i1 %Cmp72, %Cmp24
  br i1 %Cmp79, label %CF, label %CF80

CF80:                                             ; preds = %CF86
  store i8 %E26, ptr %PC70, align 1
  store i16 16293, ptr %Sl16, align 2
  store i32 %E12, ptr %Sl16, align 4
  store i32 %Sl71, ptr %0, align 4
  store i32 %3, ptr %PC70, align 4
  ret void
}
