xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 196;
 -8.46899;23.90931;2.34142;,
 -9.67503;18.80439;1.89717;,
 -7.79041;19.02599;4.32161;,
 -6.45633;21.48193;4.93871;,
 -11.29739;17.30845;-2.52301;,
 -8.70507;17.68749;1.80453;,
 -10.07162;14.67279;-2.69345;,
 -6.15503;18.55718;4.12646;,
 -3.15994;17.80665;6.39907;,
 -3.76497;19.31815;4.04174;,
 -7.41596;14.97438;3.67764;,
 -3.82644;7.38667;6.70494;,
 -5.63831;11.89753;5.92610;,
 -9.20609;9.27786;3.32975;,
 -3.80645;7.93666;9.12682;,
 -5.31177;12.30555;8.34623;,
 -1.14313;8.31675;10.13391;,
 -1.14300;12.31254;9.72057;,
 -1.14313;3.61354;8.29297;,
 -3.44635;3.73782;7.46581;,
 -1.14313;1.81913;5.29479;,
 -3.58929;3.51020;5.98811;,
 -5.71710;4.57706;4.59430;,
 -11.56971;7.42211;2.78726;,
 -9.53746;8.63323;-4.76264;,
 -1.14313;2.39194;3.91141;,
 -1.14300;16.37261;8.02881;,
 -6.32414;13.75331;7.08207;,
 -1.14300;17.93402;5.03907;,
 -4.29149;3.02434;-0.55195;,
 -2.94574;2.35383;-3.81374;,
 -1.14313;1.98730;-0.23199;,
 -8.68494;2.25652;-4.31087;,
 -6.02229;4.90266;-4.81507;,
 -11.55803;7.54435;-4.60749;,
 -9.06892;2.70438;4.71536;,
 -7.91671;0.51913;-0.87863;,
 -2.97473;0.71012;-4.28401;,
 -3.96441;4.25898;-6.89391;,
 -1.14300;-1.26521;-4.29234;,
 -2.41868;-1.41312;-6.59439;,
 -3.79155;3.88076;-8.62001;,
 -3.07190;3.62065;-11.95642;,
 -1.14313;2.59487;-13.49315;,
 -1.14300;-2.84048;-8.04720;,
 -4.81223;8.27878;-9.44367;,
 -4.85988;7.70756;-7.62002;,
 -6.22550;10.07428;-6.80199;,
 -6.20254;10.57369;-8.42987;,
 -7.47126;11.47304;-5.68343;,
 -8.74601;13.45978;-4.67901;,
 -9.10449;14.24520;-6.19134;,
 -7.48267;11.95968;-7.55467;,
 -2.08933;10.11694;-9.47553;,
 -3.00546;11.09430;-8.80040;,
 -1.14313;10.74613;-8.09565;,
 -1.14313;9.93993;-9.73078;,
 -1.14313;5.37320;-12.63353;,
 -2.16153;11.13456;-7.75503;,
 -3.53668;13.33724;-7.61330;,
 -7.47314;16.63096;-5.81418;,
 -6.23958;16.88274;-4.46872;,
 -2.78012;13.67385;-6.74455;,
 -7.70318;21.34197;-1.61868;,
 -9.32648;22.07061;-1.90134;,
 -6.89562;23.50776;1.89474;,
 -1.14300;14.84230;-7.07002;,
 -4.20036;17.56575;-5.11614;,
 -4.45375;19.71342;-4.30470;,
 -2.34084;15.62852;-6.48872;,
 -4.30921;18.18459;-7.31643;,
 -7.21880;23.36306;-1.48298;,
 -5.36224;21.15500;-5.92663;,
 -1.14300;15.63215;-8.79623;,
 -4.25995;23.18459;-7.21294;,
 -1.14300;20.92095;-8.90831;,
 -2.12530;22.45781;-7.18103;,
 -1.14300;21.81680;-7.78054;,
 -0.16056;22.45781;-7.18103;,
 -5.91775;25.82963;-5.96315;,
 -4.54649;26.01901;-5.26712;,
 -5.35875;27.12990;2.69681;,
 -6.80610;25.03026;1.87930;,
 -8.43624;24.80262;-2.24238;,
 -5.90164;27.07445;4.17518;,
 -0.19680;10.11694;-9.47553;,
 0.71934;11.09430;-8.80040;,
 2.52612;8.27878;-9.44367;,
 -0.12473;11.13456;-7.75503;,
 0.49399;13.67385;-6.74455;,
 1.25068;13.33724;-7.61330;,
 5.18728;16.63096;-5.81418;,
 3.95373;16.88274;-4.46872;,
 5.41732;21.34209;-1.61868;,
 7.04062;22.07061;-1.90134;,
 4.60963;23.50776;1.89474;,
 1.91437;17.56575;-5.11614;,
 2.16775;19.71342;-4.30470;,
 2.02335;18.18474;-7.31643;,
 0.05499;15.62852;-6.48872;,
 4.93294;23.36306;-1.48287;,
 3.07639;21.15500;-5.92663;,
 6.15039;24.80262;-2.24238;,
 1.97409;23.18459;-7.21294;,
 0.95261;23.72665;-6.65315;,
 2.26064;26.01901;-5.26712;,
 4.52011;25.03026;1.87946;,
 3.07289;27.12990;2.69681;,
 2.03503;25.56698;4.56423;,
 1.84833;27.81049;3.82338;,
 1.17794;28.05421;3.90339;,
 3.40050;25.64991;5.42375;,
 3.61565;27.07445;4.17518;,
 4.17035;21.48193;4.93871;,
 2.42760;20.59722;4.57791;,
 3.86904;18.55718;4.12646;,
 1.47912;19.31815;4.04174;,
 5.12997;14.97438;3.67764;,
 5.50442;19.02599;4.32161;,
 6.41922;17.68749;1.80453;,
 6.18313;23.90931;2.34142;,
 7.38917;18.80439;1.89717;,
 9.01140;17.30859;-2.52301;,
 7.78549;14.67279;-2.69345;,
 0.87409;17.80665;6.39907;,
 4.03815;13.75331;7.08207;,
 3.02564;12.30555;8.34623;,
 1.54032;7.38667;6.70494;,
 3.35219;11.89753;5.92610;,
 1.52032;7.93666;9.12682;,
 1.16023;3.73782;7.46581;,
 1.30317;3.51033;5.98811;,
 3.43097;4.57706;4.59445;,
 6.91996;9.27786;3.32975;,
 9.28345;7.42224;2.78726;,
 7.25134;8.63323;-4.76264;,
 2.00536;3.02434;-0.55195;,
 0.65961;2.35383;-3.81374;,
 3.73617;4.90266;-4.81507;,
 9.27190;7.54435;-4.60736;,
 6.39881;2.25652;-4.31087;,
 5.63059;0.51913;-0.87863;,
 6.78280;2.70438;4.71548;,
 0.68861;0.71012;-4.28401;,
 1.67829;4.25898;-6.89391;,
 0.13256;-1.41312;-6.59439;,
 1.50529;3.88076;-8.62001;,
 0.78578;3.62065;-11.95642;,
 2.57375;7.70756;-7.62002;,
 3.93936;10.07428;-6.80199;,
 3.91642;10.57369;-8.42987;,
 5.18500;11.47304;-5.68343;,
 5.19667;11.95968;-7.55467;,
 6.81850;14.24520;-6.19134;,
 -2.67785;20.66256;4.30668;,
 -4.01125;22.50667;3.90701;,
 -4.71345;20.59722;4.57791;,
 -4.32088;25.56698;4.56423;,
 -5.68636;25.64991;5.42375;,
 -4.08695;25.27948;3.85384;,
 -3.46393;28.05421;3.90339;,
 -4.75171;27.35912;3.31794;,
 -2.68335;25.12594;-7.71059;,
 -1.14300;24.25868;-8.19095;,
 0.39749;25.12594;-7.71059;,
 -1.14300;26.39064;6.49758;,
 -1.14300;25.44094;4.08550;,
 0.34394;27.33390;3.91344;,
 1.80096;25.27948;3.85384;,
 0.88201;26.81754;5.35448;,
 1.48099;25.10876;4.61429;,
 1.81881;22.95065;4.32535;,
 1.72527;22.50667;3.90701;,
 -1.14300;25.28219;6.66991;,
 0.30972;21.46705;5.36565;,
 -1.14300;18.90465;6.42792;,
 0.39186;20.66256;4.30668;,
 -4.10466;22.95065;4.32535;,
 -2.59571;21.46705;5.36565;,
 -3.76685;25.10876;4.61429;,
 -3.16800;26.81754;5.35448;,
 -2.62980;27.33390;3.91344;,
 2.46572;27.35912;3.31794;,
 -7.13197;25.43693;-4.17571;,
 -3.23846;23.72665;-6.65315;,
 -4.13433;27.81049;3.82338;,
 4.84611;25.43693;-4.17571;,
 6.46001;13.45978;-4.67901;,
 -1.14300;24.72506;-9.42490;,
 0.50594;25.69260;-9.10492;,
 -3.91636;26.19791;-7.32273;,
 -4.09433;26.76643;-8.97368;,
 -2.79180;25.69260;-9.10492;,
 1.80835;26.76643;-8.97368;,
 1.63051;26.19791;-7.32273;,
 3.63189;25.82963;-5.96315;;
 
 356;
 3;0,1,2;,
 3;2,3,0;,
 3;1,0,4;,
 3;2,1,5;,
 3;5,1,4;,
 3;4,6,5;,
 3;3,2,7;,
 3;2,5,7;,
 3;8,9,10;,
 3;11,12,13;,
 3;11,14,15;,
 3;14,16,17;,
 3;18,16,14;,
 3;14,19,18;,
 3;19,14,11;,
 3;18,19,20;,
 3;20,19,21;,
 3;11,21,19;,
 3;11,22,21;,
 3;23,13,24;,
 3;21,25,20;,
 3;26,8,27;,
 3;26,27,15;,
 3;8,26,28;,
 3;7,10,9;,
 3;28,9,8;,
 3;25,21,29;,
 3;30,31,29;,
 3;32,33,29;,
 3;34,24,33;,
 3;35,36,29;,
 3;21,22,29;,
 3;37,30,38;,
 3;37,39,31;,
 3;39,37,40;,
 3;40,37,41;,
 3;38,41,37;,
 3;41,42,40;,
 3;40,42,43;,
 3;39,40,44;,
 3;42,41,45;,
 3;41,38,46;,
 3;46,45,41;,
 3;45,46,47;,
 3;46,24,47;,
 3;47,48,45;,
 3;47,24,49;,
 3;49,50,51;,
 3;49,52,48;,
 3;48,47,49;,
 3;53,45,54;,
 3;55,53,54;,
 3;55,56,53;,
 3;53,57,45;,
 3;56,57,53;,
 3;57,42,45;,
 3;54,58,55;,
 3;58,54,59;,
 3;60,61,62;,
 3;63,61,60;,
 3;60,64,63;,
 3;65,63,64;,
 3;58,66,55;,
 3;61,67,62;,
 3;68,67,61;,
 3;69,67,70;,
 3;70,67,68;,
 3;68,61,63;,
 3;63,71,68;,
 3;68,72,70;,
 3;70,73,69;,
 3;70,72,74;,
 3;74,75,70;,
 3;70,75,73;,
 3;75,76,77;,
 3;75,77,78;,
 3;74,79,80;,
 3;74,76,75;,
 3;65,81,82;,
 3;68,71,83;,
 3;65,82,71;,
 3;71,63,65;,
 3;64,60,51;,
 3;64,51,4;,
 3;64,0,65;,
 3;65,0,84;,
 3;48,59,54;,
 3;54,45,48;,
 3;42,57,43;,
 3;55,85,56;,
 3;56,85,57;,
 3;55,86,85;,
 3;85,87,57;,
 3;85,86,87;,
 3;86,55,88;,
 3;88,89,90;,
 3;91,90,89;,
 3;91,92,93;,
 3;93,94,91;,
 3;94,93,95;,
 3;88,55,66;,
 3;92,89,96;,
 3;97,92,96;,
 3;98,96,99;,
 3;97,96,98;,
 3;93,92,97;,
 3;97,100,93;,
 3;98,101,97;,
 3;97,101,102;,
 3;99,73,98;,
 3;103,101,98;,
 3;98,75,103;,
 3;98,73,75;,
 3;103,104,105;,
 3;95,106,107;,
 3;108,109,110;,
 3;100,106,95;,
 3;95,93,100;,
 3;108,111,112;,
 3;113,111,108;,
 3;108,114,113;,
 3;113,114,115;,
 3;115,114,116;,
 3;116,117,115;,
 3;115,118,113;,
 3;118,115,119;,
 3;120,111,113;,
 3;120,113,118;,
 3;118,119,121;,
 3;118,121,120;,
 3;121,122,120;,
 3;122,121,119;,
 3;119,123,122;,
 3;124,116,28;,
 3;28,26,124;,
 3;26,125,124;,
 3;124,125,117;,
 3;26,126,125;,
 3;127,128,126;,
 3;129,16,18;,
 3;129,126,17;,
 3;127,129,130;,
 3;18,20,130;,
 3;18,130,129;,
 3;130,131,127;,
 3;131,130,20;,
 3;20,25,131;,
 3;127,131,132;,
 3;127,132,133;,
 3;134,133,132;,
 3;134,135,133;,
 3;25,31,136;,
 3;137,138,136;,
 3;139,140,138;,
 3;140,141,136;,
 3;142,132,136;,
 3;131,136,132;,
 3;143,31,39;,
 3;144,137,143;,
 3;39,145,143;,
 3;143,146,144;,
 3;146,143,145;,
 3;145,147,146;,
 3;57,87,147;,
 3;147,87,146;,
 3;43,147,145;,
 3;39,44,145;,
 3;148,144,146;,
 3;146,87,148;,
 3;149,148,87;,
 3;148,149,135;,
 3;87,150,149;,
 3;149,151,135;,
 3;151,152,153;,
 3;151,149,150;,
 3;150,152,151;,
 3;150,87,86;,
 3;86,90,150;,
 3;94,153,91;,
 3;94,122,153;,
 3;95,120,94;,
 3;147,43,57;,
 3;23,35,22;,
 3;23,24,34;,
 3;9,28,154;,
 3;9,154,155;,
 3;9,156,7;,
 3;7,156,3;,
 3;3,156,157;,
 3;157,158,3;,
 3;9,155,156;,
 3;155,159,156;,
 3;159,157,156;,
 3;157,159,160;,
 3;157,161,84;,
 3;0,3,158;,
 3;0,158,84;,
 3;43,44,40;,
 3;77,76,162;,
 3;77,163,164;,
 3;165,166,167;,
 3;168,110,169;,
 3;168,170,171;,
 3;171,172,168;,
 3;171,170,173;,
 3;173,170,169;,
 3;171,173,174;,
 3;173,175,174;,
 3;172,171,174;,
 3;176,172,174;,
 3;176,174,175;,
 3;175,28,176;,
 3;116,176,28;,
 3;116,172,176;,
 3;30,37,31;,
 3;69,73,66;,
 3;177,178,173;,
 3;177,173,179;,
 3;177,179,159;,
 3;173,180,179;,
 3;159,179,180;,
 3;159,155,177;,
 3;173,178,175;,
 3;154,178,155;,
 3;155,178,177;,
 3;175,178,154;,
 3;154,28,175;,
 3;166,181,180;,
 3;166,173,169;,
 3;4,0,64;,
 3;134,139,135;,
 3;116,114,172;,
 3;172,114,168;,
 3;168,114,108;,
 3;95,182,112;,
 3;145,44,43;,
 3;137,31,143;,
 3;99,66,73;,
 3;120,112,111;,
 3;103,75,78;,
 3;122,94,120;,
 3;6,4,51;,
 3;10,7,5;,
 3;10,5,6;,
 3;13,10,6;,
 3;10,13,12;,
 3;27,10,12;,
 3;10,27,8;,
 3;12,15,27;,
 3;15,12,11;,
 3;17,15,14;,
 3;13,22,11;,
 3;22,13,23;,
 3;17,26,15;,
 3;29,31,25;,
 3;29,33,30;,
 3;33,32,34;,
 3;29,36,32;,
 3;29,22,35;,
 3;33,38,30;,
 3;33,24,38;,
 3;24,46,38;,
 3;24,6,50;,
 3;24,50,49;,
 3;51,50,6;,
 3;51,52,49;,
 3;24,13,6;,
 3;59,62,58;,
 3;62,59,60;,
 3;66,58,62;,
 3;62,67,69;,
 3;66,62,69;,
 3;83,72,68;,
 3;83,183,72;,
 3;184,76,74;,
 3;160,185,157;,
 3;51,60,59;,
 3;59,48,52;,
 3;59,52,51;,
 3;90,86,88;,
 3;89,92,91;,
 3;66,89,88;,
 3;66,99,89;,
 3;89,99,96;,
 3;102,101,186;,
 3;104,103,78;,
 3;102,100,97;,
 3;117,119,115;,
 3;117,123,119;,
 3;153,122,123;,
 3;133,123,117;,
 3;117,128,133;,
 3;128,117,125;,
 3;117,116,124;,
 3;17,126,26;,
 3;125,126,128;,
 3;133,128,127;,
 3;126,129,127;,
 3;17,16,129;,
 3;136,131,25;,
 3;136,31,137;,
 3;136,138,140;,
 3;138,135,139;,
 3;136,141,142;,
 3;138,137,144;,
 3;138,144,135;,
 3;135,144,148;,
 3;135,187,123;,
 3;135,151,187;,
 3;123,187,153;,
 3;153,187,151;,
 3;135,123,133;,
 3;90,152,150;,
 3;153,152,90;,
 3;90,91,153;,
 3;188,163,162;,
 3;184,162,76;,
 3;188,189,164;,
 3;132,142,134;,
 3;110,168,108;,
 3;104,78,164;,
 3;183,74,72;,
 3;80,184,74;,
 3;190,191,192;,
 3;192,162,190;,
 3;181,166,165;,
 3;82,83,71;,
 3;161,81,65;,
 3;161,157,185;,
 3;186,101,103;,
 3;106,100,102;,
 3;182,109,108;,
 3;182,95,107;,
 3;112,182,108;,
 3;112,120,95;,
 3;84,158,157;,
 3;84,161,65;,
 3;162,192,188;,
 3;162,163,77;,
 3;190,162,184;,
 3;189,193,194;,
 3;194,164,189;,
 3;164,163,188;,
 3;169,170,168;,
 3;180,160,159;,
 3;180,173,166;,
 3;180,181,160;,
 3;169,167,166;,
 3;169,110,167;,
 3;80,190,184;,
 3;183,79,74;,
 3;105,104,194;,
 3;194,104,164;,
 3;164,78,77;,
 3;105,195,103;,
 3;186,103,195;;
 
 MeshMaterialList {
  2;
  356;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.320000;0.592800;0.336800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "allegorica_d.tga";
   }
  }
  Material {
   0.460800;0.356000;0.363200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "body_d.tga";
   }
  }
 }
 MeshNormals {
  314;
  -0.846580;0.226463;0.481682;,
  -0.826429;-0.235498;0.511425;,
  -0.527734;-0.321790;0.786097;,
  -0.120567;-0.091603;0.988470;,
  -0.952936;-0.187586;0.238170;,
  -0.698629;-0.443088;0.561774;,
  -0.976387;-0.208395;0.056913;,
  -0.103254;-0.309610;0.945241;,
  -0.274763;0.740769;0.612999;,
  -0.132418;0.094075;0.986719;,
  -0.842364;0.174627;0.509831;,
  -0.874784;-0.203612;0.439654;,
  -0.855236;-0.244888;0.456729;,
  -0.725020;0.016165;0.688539;,
  -0.977005;-0.206041;0.054854;,
  -0.918075;-0.366264;0.151618;,
  -0.000008;-0.137956;0.990438;,
  -0.000000;0.187178;0.982326;,
  -0.000008;-0.567336;0.823486;,
  -0.389013;-0.734095;0.556573;,
  0.000004;-0.988229;0.152982;,
  -0.687859;-0.700526;0.190034;,
  -0.556585;-0.339373;0.758313;,
  -0.544657;0.838572;-0.012089;,
  -0.825997;0.441379;-0.350589;,
  -0.131921;-0.991065;0.019664;,
  0.000002;0.577037;0.816718;,
  -0.486634;0.506083;0.712086;,
  0.000002;0.689156;0.724613;,
  -0.182871;-0.968345;0.169902;,
  -0.505823;-0.855182;-0.113165;,
  -0.000002;-0.968976;0.247155;,
  0.375571;-0.550457;-0.745616;,
  0.267652;-0.433300;-0.860589;,
  -0.070947;-0.070487;-0.994986;,
  0.479511;-0.787555;0.387075;,
  0.570493;-0.820328;-0.040003;,
  -0.898037;-0.341387;0.277461;,
  -0.866270;-0.432194;-0.250568;,
  -0.611429;-0.676402;0.410652;,
  -0.842396;-0.536566;-0.049665;,
  -0.958971;-0.268911;-0.089787;,
  -0.816056;-0.145469;-0.559367;,
  -0.750442;-0.257884;-0.608550;,
  -0.757138;-0.652835;-0.023428;,
  -0.915592;-0.253864;-0.311842;,
  -0.857934;-0.280171;-0.430642;,
  -0.819349;-0.301009;-0.487914;,
  -0.818906;-0.549601;-0.165325;,
  -0.785172;-0.242286;-0.569915;,
  -0.840298;-0.257367;-0.477138;,
  -0.845465;-0.517071;-0.133516;,
  -0.809612;-0.569253;-0.143105;,
  -0.067100;0.643703;-0.762328;,
  0.135056;0.613164;-0.778325;,
  0.000006;0.783218;-0.621747;,
  -0.000003;0.744928;-0.667144;,
  -0.000010;0.417489;-0.908682;,
  0.550078;0.642022;-0.534062;,
  0.147618;0.496046;-0.855656;,
  0.193285;0.626036;-0.755460;,
  0.022324;0.579249;-0.814845;,
  0.041654;0.501976;-0.863878;,
  0.458180;0.642967;-0.613730;,
  -0.033919;0.697362;-0.715916;,
  -0.039384;0.752409;-0.657518;,
  0.000003;0.244187;-0.969728;,
  -0.390651;0.247489;-0.886646;,
  -0.479034;0.278493;-0.832447;,
  -0.693959;-0.665341;-0.275215;,
  -0.838615;-0.294914;-0.457985;,
  -0.879894;0.238473;-0.410996;,
  -0.885454;-0.240523;-0.397644;,
  -0.640068;-0.503257;-0.580556;,
  -0.474983;0.171965;-0.863029;,
  -0.022514;0.408861;-0.912319;,
  -0.780541;-0.115068;-0.614422;,
  0.201845;0.705894;-0.678949;,
  0.000009;0.783020;-0.621996;,
  -0.201840;0.705899;-0.678945;,
  0.227796;0.566635;-0.791855;,
  0.312666;0.558873;-0.768050;,
  -0.728490;-0.562424;-0.391128;,
  -0.635912;-0.748233;-0.189111;,
  0.838691;0.264666;0.475971;,
  0.775151;-0.587852;0.231453;,
  0.629516;0.626484;0.459595;,
  -0.642345;0.104417;0.759269;,
  0.385112;0.587512;0.711701;,
  -0.866727;-0.147101;0.476598;,
  -0.866585;-0.493894;-0.071410;,
  -0.351240;0.571877;-0.741341;,
  0.067100;0.643700;-0.762331;,
  -0.135036;0.613161;-0.778331;,
  0.320924;0.358099;-0.876797;,
  -0.229282;0.553662;-0.800555;,
  0.024902;0.467383;-0.883704;,
  -0.147590;0.496045;-0.855662;,
  -0.193268;0.626033;-0.755467;,
  -0.473537;0.678849;-0.561184;,
  -0.458156;0.642975;-0.613739;,
  0.033944;0.697360;-0.715917;,
  0.039395;0.752412;-0.657514;,
  0.390660;0.247475;-0.886646;,
  0.479003;0.278514;-0.832458;,
  0.838616;-0.294915;-0.457983;,
  0.693954;-0.665338;-0.275233;,
  0.970273;-0.220140;-0.100542;,
  0.885455;-0.240538;-0.397632;,
  0.866583;-0.493898;-0.071402;,
  0.286916;0.347261;-0.892798;,
  0.780540;-0.115066;-0.614424;,
  -0.312668;0.558873;-0.768049;,
  -0.227797;0.566635;-0.791854;,
  -0.164248;0.541771;-0.824322;,
  0.642240;0.104327;0.759371;,
  0.866688;-0.147133;0.476658;,
  0.494229;0.309402;0.812409;,
  0.583227;0.546683;-0.600820;,
  -0.539008;0.179859;0.822874;,
  0.637751;0.291464;0.712968;,
  -0.527492;0.240585;0.814783;,
  -0.413796;0.608604;0.677033;,
  -0.209590;-0.186983;0.959745;,
  -0.465008;-0.098061;0.879859;,
  0.103246;-0.309609;0.945242;,
  -0.042837;-0.060124;0.997271;,
  0.770623;0.061040;0.634361;,
  0.453819;-0.455025;0.766160;,
  0.698626;-0.443101;0.561768;,
  0.846578;0.226463;0.481685;,
  0.826429;-0.235498;0.511426;,
  0.952936;-0.187599;0.238160;,
  0.976384;-0.208411;0.056919;,
  0.274774;0.740761;0.613002;,
  0.486635;0.506068;0.712096;,
  0.331620;0.297058;0.895424;,
  0.874780;-0.203609;0.439662;,
  0.855227;-0.244915;0.456731;,
  0.332312;-0.144453;0.932042;,
  0.921378;-0.370790;0.116518;,
  0.687855;-0.700531;0.190031;,
  0.413942;-0.005599;0.910286;,
  0.725022;0.016167;0.688536;,
  0.205685;0.187046;0.960577;,
  0.825999;0.441375;-0.350591;,
  0.290710;-0.948644;0.124748;,
  0.776298;-0.623983;0.089483;,
  0.614797;-0.734123;-0.288250;,
  0.070976;-0.070499;-0.994984;,
  -0.267644;-0.433293;-0.860595;,
  -0.570492;-0.820328;-0.040006;,
  -0.479511;-0.787559;0.387066;,
  0.898041;-0.341384;0.277451;,
  0.866260;-0.432200;-0.250592;,
  0.842409;-0.536544;-0.049669;,
  0.958967;-0.268920;-0.089800;,
  0.816055;-0.145469;-0.559369;,
  0.857926;-0.280178;-0.430654;,
  0.819360;-0.300995;-0.487905;,
  0.818902;-0.549619;-0.165286;,
  0.811505;-0.335577;-0.478381;,
  0.809582;-0.569320;-0.143010;,
  0.845452;-0.517100;-0.133483;,
  -0.699321;-0.257957;0.666640;,
  0.349227;0.048241;0.935796;,
  0.465043;-0.098060;0.879841;,
  0.539044;0.179866;0.822849;,
  0.527488;0.240593;0.814783;,
  0.854990;-0.086107;0.511446;,
  -0.615749;-0.751851;-0.235742;,
  -0.531467;-0.795323;-0.291555;,
  -0.606660;-0.516092;-0.604659;,
  0.615748;-0.751846;-0.235757;,
  0.635945;-0.748197;-0.189145;,
  -0.000016;-0.165747;-0.986168;,
  0.606637;-0.516100;-0.604675;,
  0.728494;-0.562413;-0.391137;,
  0.961588;0.102493;0.254644;,
  0.839845;0.072687;0.537937;,
  0.785958;0.023431;0.617835;,
  0.865665;-0.114868;0.487268;,
  0.905229;-0.364889;0.217755;,
  0.611576;-0.053118;0.789400;,
  0.765029;-0.298338;0.570723;,
  0.825592;-0.277743;0.491179;,
  0.699315;-0.257954;0.666648;,
  -0.865625;-0.114836;0.487345;,
  -0.765034;-0.298305;0.570734;,
  -0.785929;0.023382;0.617875;,
  -0.839832;0.072631;0.537965;,
  0.164247;0.541770;-0.824323;,
  -0.494224;0.309373;0.812423;,
  0.840289;-0.257390;-0.477142;,
  -0.332323;-0.144446;0.932039;,
  -0.993611;-0.089042;0.069343;,
  -0.611699;0.790183;-0.037897;,
  -0.331618;0.297066;0.895423;,
  0.083542;-0.152759;0.984726;,
  0.264758;0.841222;0.471432;,
  0.541755;-0.679795;-0.494348;,
  -0.505011;-0.175388;-0.845105;,
  -0.405936;-0.370758;-0.835317;,
  -0.929135;-0.086464;0.359489;,
  -0.816116;-0.567210;-0.110577;,
  -0.252106;0.390166;-0.885558;,
  -0.297155;0.251791;-0.921032;,
  -0.366352;0.242209;-0.898399;,
  -0.916614;-0.394359;-0.065570;,
  -0.893563;-0.447403;0.037086;,
  -0.765103;0.290925;-0.574439;,
  0.130237;0.776351;-0.616698;,
  0.298941;0.683762;-0.665661;,
  -0.879765;0.134048;0.456119;,
  -0.910001;-0.376795;0.172987;,
  -0.367396;0.379572;-0.849085;,
  -0.642042;0.354466;-0.679806;,
  0.010294;0.761395;-0.648207;,
  -0.164116;0.388124;-0.906877;,
  0.410529;0.295300;-0.862707;,
  0.916620;-0.394350;-0.065539;,
  0.893551;-0.447425;0.037114;,
  0.765088;0.290953;-0.574445;,
  0.640044;-0.503260;-0.580580;,
  0.879727;0.134001;0.456206;,
  0.993932;0.059371;0.092597;,
  0.781075;0.202886;0.590559;,
  0.721954;0.128793;0.679849;,
  0.680644;0.192084;0.706985;,
  -0.264742;0.841224;0.471438;,
  0.674526;0.599204;0.431242;,
  0.918067;-0.366283;0.151624;,
  0.977005;-0.206040;0.054858;,
  0.291649;-0.633108;0.717018;,
  0.598545;-0.740149;-0.306470;,
  0.544655;0.838573;-0.012092;,
  0.611692;0.790187;-0.037897;,
  -0.155029;-0.299529;-0.941408;,
  -0.528963;-0.703570;-0.474540;,
  -0.566316;-0.792591;-0.226024;,
  -0.463087;-0.804874;0.371118;,
  0.505628;-0.854672;0.117798;,
  0.611454;-0.676381;0.410649;,
  0.922566;-0.354652;-0.151969;,
  0.750434;-0.257872;-0.608564;,
  0.757170;-0.652798;-0.023429;,
  0.505020;-0.175388;-0.845100;,
  0.843597;-0.520949;-0.130218;,
  0.164115;0.388119;-0.906879;,
  0.367402;0.379564;-0.849086;,
  0.642040;0.354458;-0.679812;,
  -0.010293;0.761395;-0.648207;,
  -0.205667;0.187034;0.960583;,
  -0.139451;0.310384;0.940327;,
  -0.473530;0.880669;0.013810;,
  0.413784;0.608627;0.677020;,
  -0.781073;0.202873;0.590565;,
  -0.785619;0.336399;0.519267;,
  -0.505968;-0.217878;-0.834581;,
  -0.638077;-0.276113;-0.718762;,
  0.505921;-0.217877;-0.834610;,
  0.865828;-0.410113;0.286617;,
  -0.349197;0.048235;0.935807;,
  -0.892334;-0.109541;0.437881;,
  -0.624109;-0.710494;-0.325096;,
  -0.611593;-0.053122;0.789387;,
  -0.961558;0.102450;0.254776;,
  -0.905221;-0.364829;0.217888;,
  -0.825594;-0.277741;0.491177;,
  -0.865829;-0.410111;0.286616;,
  0.649484;0.713763;0.262130;,
  0.628309;0.704335;0.330364;,
  -0.649476;0.713780;0.262104;,
  -0.582667;0.811182;0.049828;,
  -0.628325;0.704336;0.330333;,
  -0.924788;0.379830;0.022297;,
  0.473532;0.880669;0.013803;,
  -0.854919;-0.086101;0.511567;,
  0.351237;0.571877;-0.741343;,
  0.892322;-0.109543;0.437907;,
  0.624061;-0.710528;-0.325111;,
  0.785618;0.336446;0.519239;,
  0.924793;0.379817;0.022304;,
  -0.887051;-0.430960;0.165575;,
  -0.586085;-0.785501;-0.198725;,
  0.463088;-0.804868;0.371128;,
  -0.376088;0.202851;-0.904107;,
  -0.637748;0.291457;0.712973;,
  -0.159462;0.418726;-0.894002;,
  0.376121;0.202804;-0.904104;,
  0.887027;-0.431010;0.165569;,
  0.678213;0.527104;0.512044;,
  0.159461;0.418722;-0.894005;,
  -0.537209;-0.788977;-0.298198;,
  -0.720994;-0.330530;-0.609030;,
  0.531433;-0.795342;-0.291564;,
  0.139465;0.310394;0.940322;,
  -0.838668;0.264648;0.476022;,
  0.720992;-0.330530;-0.609033;,
  0.638046;-0.276112;-0.718790;,
  -0.775181;-0.587819;0.231440;,
  -0.728917;0.218892;0.648665;,
  -0.720550;0.270718;0.638373;,
  0.728882;0.218871;0.648711;,
  0.720552;0.270759;0.638353;,
  -0.385125;0.587492;0.711711;,
  -0.583227;0.546683;-0.600820;,
  0.537174;-0.788997;-0.298206;,
  0.582668;0.811181;0.049827;,
  -0.629545;0.626488;0.459550;,
  -0.894976;-0.327562;-0.302855;,
  -0.784563;-0.217344;-0.580709;,
  0.894976;-0.327562;-0.302855;,
  0.784563;-0.217344;-0.580709;;
  356;
  3;0,1,2;,
  3;2,3,0;,
  3;1,0,4;,
  3;2,1,5;,
  3;5,1,4;,
  3;4,6,5;,
  3;3,2,7;,
  3;2,5,7;,
  3;8,9,10;,
  3;11,12,13;,
  3;11,14,15;,
  3;194,16,17;,
  3;18,16,194;,
  3;194,19,18;,
  3;195,14,11;,
  3;18,19,20;,
  3;20,19,21;,
  3;11,21,195;,
  3;11,22,21;,
  3;23,196,24;,
  3;21,25,20;,
  3;26,8,27;,
  3;26,27,197;,
  3;8,26,28;,
  3;7,198,198;,
  3;28,199,8;,
  3;25,21,29;,
  3;30,31,29;,
  3;32,33,200;,
  3;34,201,202;,
  3;35,36,29;,
  3;21,22,29;,
  3;37,203,38;,
  3;37,39,31;,
  3;39,37,40;,
  3;40,37,41;,
  3;38,41,37;,
  3;41,42,40;,
  3;40,42,43;,
  3;39,40,44;,
  3;42,41,45;,
  3;41,38,46;,
  3;46,45,41;,
  3;45,46,47;,
  3;46,201,47;,
  3;47,48,45;,
  3;47,201,49;,
  3;204,50,51;,
  3;204,52,48;,
  3;48,47,49;,
  3;53,205,54;,
  3;55,53,54;,
  3;55,56,53;,
  3;53,57,205;,
  3;56,57,53;,
  3;57,42,45;,
  3;54,58,55;,
  3;58,54,59;,
  3;60,61,62;,
  3;63,61,60;,
  3;60,64,63;,
  3;65,63,64;,
  3;206,66,55;,
  3;207,67,207;,
  3;68,67,61;,
  3;69,208,70;,
  3;70,208,209;,
  3;68,61,210;,
  3;210,71,68;,
  3;209,72,70;,
  3;70,73,69;,
  3;70,72,74;,
  3;74,75,70;,
  3;70,75,73;,
  3;211,77,78;,
  3;75,78,79;,
  3;212,81,80;,
  3;212,77,75;,
  3;213,87,89;,
  3;209,214,90;,
  3;213,89,214;,
  3;71,210,213;,
  3;64,60,215;,
  3;64,215,216;,
  3;64,217,65;,
  3;65,217,91;,
  3;218,59,54;,
  3;54,205,218;,
  3;42,57,43;,
  3;55,92,56;,
  3;56,92,57;,
  3;55,93,92;,
  3;92,94,57;,
  3;92,93,94;,
  3;93,55,95;,
  3;95,96,97;,
  3;98,97,96;,
  3;98,99,100;,
  3;100,101,98;,
  3;101,100,102;,
  3;95,55,66;,
  3;219,96,103;,
  3;104,219,103;,
  3;105,220,106;,
  3;221,220,105;,
  3;222,219,104;,
  3;104,107,222;,
  3;105,108,221;,
  3;221,108,109;,
  3;106,223,105;,
  3;110,108,105;,
  3;105,75,110;,
  3;105,223,75;,
  3;110,114,113;,
  3;224,116,115;,
  3;119,117,120;,
  3;225,116,224;,
  3;224,222,107;,
  3;119,121,122;,
  3;123,121,119;,
  3;119,124,123;,
  3;123,124,125;,
  3;125,124,126;,
  3;126,127,125;,
  3;125,128,123;,
  3;128,125,129;,
  3;130,226,227;,
  3;130,227,228;,
  3;128,129,131;,
  3;128,131,130;,
  3;131,132,130;,
  3;132,131,129;,
  3;129,133,132;,
  3;134,229,28;,
  3;28,26,134;,
  3;26,135,134;,
  3;134,135,230;,
  3;26,136,135;,
  3;137,138,231;,
  3;139,16,18;,
  3;139,136,17;,
  3;137,232,140;,
  3;18,20,233;,
  3;18,233,139;,
  3;140,141,137;,
  3;141,140,20;,
  3;20,234,141;,
  3;137,141,142;,
  3;137,142,143;,
  3;144,143,142;,
  3;235,145,236;,
  3;25,31,146;,
  3;147,148,146;,
  3;149,150,237;,
  3;238,151,239;,
  3;152,240,239;,
  3;141,146,241;,
  3;153,31,242;,
  3;154,147,153;,
  3;242,155,153;,
  3;153,156,154;,
  3;156,153,155;,
  3;155,157,156;,
  3;57,94,157;,
  3;157,243,156;,
  3;244,157,155;,
  3;242,245,155;,
  3;158,154,156;,
  3;156,243,158;,
  3;159,158,243;,
  3;158,159,246;,
  3;243,160,159;,
  3;159,161,246;,
  3;247,162,163;,
  3;161,159,160;,
  3;160,162,161;,
  3;248,94,93;,
  3;93,97,248;,
  3;101,249,98;,
  3;101,250,249;,
  3;102,251,101;,
  3;157,244,57;,
  3;252,253,253;,
  3;23,24,254;,
  3;9,28,164;,
  3;9,164,165;,
  3;9,166,7;,
  3;7,166,3;,
  3;3,166,167;,
  3;167,168,3;,
  3;9,165,166;,
  3;165,169,166;,
  3;169,167,166;,
  3;167,169,84;,
  3;167,88,255;,
  3;0,3,256;,
  3;0,256,257;,
  3;43,44,40;,
  3;258,259,172;,
  3;260,175,176;,
  3;85,85,85;,
  3;178,120,179;,
  3;178,180,181;,
  3;181,182,178;,
  3;181,180,183;,
  3;183,180,179;,
  3;181,183,184;,
  3;183,185,184;,
  3;182,181,184;,
  3;186,182,184;,
  3;186,184,185;,
  3;185,261,186;,
  3;126,186,28;,
  3;126,262,186;,
  3;203,37,263;,
  3;69,73,264;,
  3;187,188,265;,
  3;187,265,189;,
  3;187,189,266;,
  3;265,190,189;,
  3;266,189,190;,
  3;266,267,187;,
  3;265,188,268;,
  3;164,188,267;,
  3;267,188,187;,
  3;268,188,164;,
  3;164,269,268;,
  3;270,86,271;,
  3;272,273,274;,
  3;4,0,275;,
  3;235,276,145;,
  3;126,124,262;,
  3;262,124,277;,
  3;277,124,119;,
  3;102,118,278;,
  3;155,245,244;,
  3;147,279,153;,
  3;106,280,223;,
  3;130,281,226;,
  3;110,75,79;,
  3;132,282,130;,
  3;6,4,51;,
  3;10,7,5;,
  3;10,5,6;,
  3;13,10,6;,
  3;10,13,12;,
  3;283,10,12;,
  3;10,27,8;,
  3;12,15,283;,
  3;15,12,11;,
  3;17,197,194;,
  3;13,22,11;,
  3;22,13,252;,
  3;17,26,197;,
  3;29,31,25;,
  3;29,284,30;,
  3;33,32,34;,
  3;200,36,32;,
  3;29,285,35;,
  3;284,38,30;,
  3;202,201,38;,
  3;201,46,38;,
  3;24,6,50;,
  3;24,50,49;,
  3;51,50,6;,
  3;51,52,49;,
  3;24,13,6;,
  3;59,62,58;,
  3;62,59,60;,
  3;66,206,62;,
  3;62,67,286;,
  3;66,62,286;,
  3;90,72,209;,
  3;90,76,72;,
  3;191,77,74;,
  3;287,192,167;,
  3;215,60,59;,
  3;59,218,288;,
  3;59,288,215;,
  3;97,93,95;,
  3;96,99,98;,
  3;66,96,95;,
  3;66,289,96;,
  3;96,289,103;,
  3;109,108,111;,
  3;114,110,79;,
  3;109,107,221;,
  3;127,129,125;,
  3;127,133,129;,
  3;163,132,133;,
  3;143,133,127;,
  3;127,138,143;,
  3;138,127,290;,
  3;127,291,134;,
  3;17,136,26;,
  3;290,231,138;,
  3;143,138,137;,
  3;231,232,137;,
  3;17,16,139;,
  3;146,141,25;,
  3;146,31,147;,
  3;239,237,150;,
  3;237,246,149;,
  3;146,151,152;,
  3;148,147,154;,
  3;148,154,246;,
  3;246,154,158;,
  3;145,193,133;,
  3;145,161,193;,
  3;133,193,163;,
  3;163,193,161;,
  3;145,133,143;,
  3;97,292,248;,
  3;249,292,97;,
  3;97,98,249;,
  3;171,293,172;,
  3;294,172,259;,
  3;295,173,176;,
  3;142,296,144;,
  3;297,277,119;,
  3;298,299,176;,
  3;76,74,72;,
  3;80,191,74;,
  3;82,83,170;,
  3;170,172,82;,
  3;300,300,300;,
  3;89,90,214;,
  3;301,87,213;,
  3;301,302,192;,
  3;111,108,110;,
  3;116,107,109;,
  3;303,117,304;,
  3;303,224,115;,
  3;122,305,119;,
  3;278,251,102;,
  3;255,168,167;,
  3;91,306,65;,
  3;172,170,171;,
  3;172,175,258;,
  3;82,172,294;,
  3;173,174,177;,
  3;177,176,173;,
  3;176,307,295;,
  3;179,180,178;,
  3;190,287,266;,
  3;271,308,270;,
  3;271,86,84;,
  3;274,309,272;,
  3;274,297,309;,
  3;310,82,294;,
  3;76,311,74;,
  3;312,298,177;,
  3;177,298,176;,
  3;176,299,260;,
  3;113,112,110;,
  3;111,110,313;;
 }
 MeshTextureCoords {
  196;
  0.198550;0.264020;,
  0.190560;0.216970;,
  0.218240;0.220600;,
  0.234470;0.238720;,
  0.145530;0.195960;,
  0.192090;0.206160;,
  0.140770;0.180190;,
  0.227040;0.212020;,
  0.270970;0.186250;,
  0.255080;0.216190;,
  0.212490;0.178680;,
  0.229870;0.097920;,
  0.227500;0.143210;,
  0.181460;0.131270;,
  0.249730;0.097990;,
  0.249250;0.140370;,
  0.273220;0.087580;,
  0.287650;0.125840;,
  0.240480;0.049740;,
  0.225680;0.061520;,
  0.209170;0.032030;,
  0.214740;0.062070;,
  0.197670;0.090710;,
  0.159030;0.117710;,
  0.126760;0.115640;,
  0.196950;0.031330;,
  0.292440;0.171000;,
  0.240510;0.161170;,
  0.285710;0.203390;,
  0.161460;0.065040;,
  0.114530;0.047210;,
  0.150540;0.029310;,
  0.152310;0.084170;,
  0.122600;0.080540;,
  0.142780;0.104150;,
  0.176960;0.103300;,
  0.170780;0.085940;,
  0.103750;0.037660;,
  0.084200;0.076680;,
  0.098570;0.013650;,
  0.076040;0.025420;,
  0.067910;0.078780;,
  0.035750;0.082760;,
  0.014390;0.072570;,
  0.057720;0.012820;,
  0.064020;0.118390;,
  0.079330;0.110150;,
  0.091600;0.132360;,
  0.079340;0.145030;,
  0.105680;0.144420;,
  0.119140;0.163650;,
  0.109890;0.175870;,
  0.091810;0.156990;,
  0.042000;0.149470;,
  0.053240;0.158690;,
  0.036780;0.166940;,
  0.031870;0.149740;,
  0.017890;0.100000;,
  0.046250;0.170070;,
  0.063180;0.181800;,
  0.109120;0.202290;,
  0.106010;0.218110;,
  0.060710;0.194200;,
  0.151180;0.254710;,
  0.158180;0.241940;,
  0.191390;0.276340;,
  0.046880;0.206800;,
  0.088680;0.229000;,
  0.104890;0.247760;,
  0.061650;0.213120;,
  0.073080;0.241330;,
  0.151590;0.277770;,
  0.095370;0.266270;,
  0.037830;0.220680;,
  0.078380;0.287740;,
  0.043420;0.268880;,
  0.056320;0.286610;,
  0.046480;0.280130;,
  0.056320;0.286610;,
  0.098300;0.312370;,
  0.085470;0.318690;,
  0.222930;0.302510;,
  0.191450;0.289970;,
  0.144500;0.299070;,
  0.230530;0.290000;,
  0.042000;0.149470;,
  0.053240;0.158690;,
  0.064020;0.118390;,
  0.046250;0.170070;,
  0.060710;0.194200;,
  0.063180;0.181800;,
  0.109120;0.202290;,
  0.106010;0.218110;,
  0.151180;0.254710;,
  0.158180;0.241940;,
  0.191390;0.276340;,
  0.088680;0.229000;,
  0.104890;0.247760;,
  0.073080;0.241330;,
  0.061650;0.213120;,
  0.151590;0.277770;,
  0.095370;0.266270;,
  0.144500;0.299070;,
  0.078380;0.287740;,
  0.067980;0.297580;,
  0.085470;0.318690;,
  0.191450;0.289970;,
  0.222930;0.302510;,
  0.246190;0.280450;,
  0.249410;0.304390;,
  0.260300;0.305400;,
  0.235900;0.277670;,
  0.230530;0.290000;,
  0.234470;0.238720;,
  0.244290;0.234460;,
  0.227040;0.212020;,
  0.255080;0.216190;,
  0.212490;0.178680;,
  0.218240;0.220600;,
  0.192090;0.206160;,
  0.198550;0.264020;,
  0.190560;0.216970;,
  0.145530;0.195960;,
  0.140770;0.180190;,
  0.270970;0.186250;,
  0.240510;0.161170;,
  0.249250;0.140370;,
  0.229870;0.097920;,
  0.227500;0.143210;,
  0.249730;0.097990;,
  0.225680;0.061520;,
  0.214740;0.062070;,
  0.197670;0.090710;,
  0.181460;0.131270;,
  0.159030;0.117710;,
  0.126760;0.115640;,
  0.161460;0.065040;,
  0.114530;0.047210;,
  0.122600;0.080540;,
  0.142780;0.104150;,
  0.152310;0.084170;,
  0.170780;0.085940;,
  0.176960;0.103300;,
  0.103750;0.037660;,
  0.084200;0.076680;,
  0.076040;0.025420;,
  0.067910;0.078780;,
  0.035750;0.082760;,
  0.079330;0.110150;,
  0.091600;0.132360;,
  0.079340;0.145030;,
  0.105680;0.144420;,
  0.091810;0.156990;,
  0.109890;0.175870;,
  0.266890;0.228290;,
  0.255500;0.245450;,
  0.244290;0.234460;,
  0.246190;0.280450;,
  0.235900;0.277670;,
  0.254220;0.276140;,
  0.260300;0.305400;,
  0.234880;0.300100;,
  0.055180;0.311740;,
  0.040560;0.300890;,
  0.055180;0.311740;,
  0.306080;0.307930;,
  0.296410;0.291710;,
  0.273910;0.301550;,
  0.254220;0.276140;,
  0.270290;0.287820;,
  0.261460;0.272500;,
  0.262140;0.251530;,
  0.255500;0.245450;,
  0.293320;0.273050;,
  0.274050;0.235520;,
  0.293410;0.212440;,
  0.266890;0.228290;,
  0.262140;0.251530;,
  0.274050;0.235520;,
  0.261460;0.272500;,
  0.270290;0.287820;,
  0.273910;0.301550;,
  0.234880;0.300100;,
  0.119610;0.306130;,
  0.067980;0.297580;,
  0.249410;0.304390;,
  0.119610;0.306130;,
  0.119140;0.163650;,
  0.030980;0.308850;,
  0.044180;0.321700;,
  0.065710;0.323210;,
  0.052080;0.333470;,
  0.044180;0.321700;,
  0.052080;0.333470;,
  0.065710;0.323210;,
  0.098300;0.312370;;
 }
}
