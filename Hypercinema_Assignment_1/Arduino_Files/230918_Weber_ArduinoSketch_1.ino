// September 18, 2023
// 7:46PM
// Proof of concept file! It works!
// - record speech
// - reading wave form in python (native python wave module)
// - identifying wave peaks using python (wav_plot.py, using scipy)
// - use python to spit out arduino code for timestamps (wav_plot.py)
// * Has successfully been used with Nano 33 IOT to fire a 12V solenoid
// * Solenoid circuiting adapter from: https://www.makerguides.com/control-a-solenoid-with-arduino/


void setup() {
  pinMode(13, OUTPUT);
}

void loop() {
  delay(493);
  digitalWrite(13, HIGH);  // 0.5331252272152879
  delay(40);
  digitalWrite(13, LOW);
  delay(64);
  digitalWrite(13, HIGH);  // 0.6377086051215303
  delay(40);
  digitalWrite(13, LOW);
  delay(119);
  digitalWrite(13, HIGH);  // 0.7968753396242579
  delay(40);
  digitalWrite(13, LOW);
  delay(210);
  digitalWrite(13, HIGH);  // 1.0460421124845487
  delay(40);
  digitalWrite(13, LOW);
  delay(147);
  digitalWrite(13, HIGH);  // 1.2333338589740148
  delay(40);
  digitalWrite(13, LOW);
  delay(560);
  // digitalWrite(13, HIGH);  // 1.8339591149574752 -- commented out, this one is a weird thing in the sound file
  delay(40);
  digitalWrite(13, LOW);
  delay(3427);
  digitalWrite(13, HIGH);  // 5.30000225883428
  delay(40);
  digitalWrite(13, LOW);
  delay(121);
  digitalWrite(13, HIGH);  // 5.461043994136124
  delay(40);
  digitalWrite(13, LOW);
  delay(71);
  digitalWrite(13, HIGH);  // 5.572502374972458
  delay(40);
  digitalWrite(13, LOW);
  delay(103);
  digitalWrite(13, HIGH);  // 5.715627435971638
  delay(40);
  digitalWrite(13, LOW);
  delay(155);
  digitalWrite(13, HIGH);  // 5.910210852235444
  delay(40);
  digitalWrite(13, LOW);
  delay(126);
  digitalWrite(13, HIGH);  // 6.076252589668263
  delay(40);
  digitalWrite(13, LOW);
  delay(76);
  digitalWrite(13, HIGH);  // 6.192919306057697
  delay(40);
  digitalWrite(13, LOW);
  delay(609);
  digitalWrite(13, HIGH);  // 6.841877915973923
  delay(40);
  digitalWrite(13, LOW);
  delay(2596);
  digitalWrite(13, HIGH);  // 9.477295705842383
  delay(40);
  digitalWrite(13, LOW);
  delay(72);
  digitalWrite(13, HIGH);  // 9.589587420367213
  delay(40);
  digitalWrite(13, LOW);
  delay(626);
  digitalWrite(13, HIGH);  // 10.255837704319731
  delay(40);
  digitalWrite(13, LOW);
  delay(109);
  digitalWrite(13, HIGH);  // 10.404171100872011
  delay(40);
  digitalWrite(13, LOW);
  delay(117);
  digitalWrite(13, HIGH);  // 10.561462834575622
  delay(40);
  digitalWrite(13, LOW);
  delay(65);
  digitalWrite(13, HIGH);  // 10.66687954617036
  delay(40);
  digitalWrite(13, LOW);
  delay(72);
  digitalWrite(13, HIGH);  // 10.77812959358457
  delay(40);
  digitalWrite(13, LOW);
  delay(143);
  digitalWrite(13, HIGH);  // 10.961046338209433
  delay(40);
  digitalWrite(13, LOW);
  delay(71);
  digitalWrite(13, HIGH);  // 11.072088052201519
  delay(40);
  digitalWrite(13, LOW);
  delay(91);
  digitalWrite(13, HIGH);  // 11.203963108406004
  delay(40);
  digitalWrite(13, LOW);
  delay(77);
  digitalWrite(13, HIGH);  // 11.320421491373313
  delay(40);
  digitalWrite(13, LOW);
  delay(110);
  digitalWrite(13, HIGH);  // 11.47062988872471
  delay(40);
  digitalWrite(13, LOW);
  delay(1021);
  digitalWrite(13, HIGH);  // 12.531463674180062
  delay(40);
  digitalWrite(13, LOW);
  delay(238);
  digitalWrite(13, HIGH);  // 12.809172125871338
  delay(40);
  digitalWrite(13, LOW);
  delay(164);
  digitalWrite(13, HIGH);  // 13.01396387981922
  delay(40);
  digitalWrite(13, LOW);
  delay(162);
  digitalWrite(13, HIGH);  // 13.215838965857365
  delay(40);
  digitalWrite(13, LOW);
  delay(73);
  digitalWrite(13, HIGH);  // 13.328130680382197
  delay(40);
  digitalWrite(13, LOW);
  delay(121);
  digitalWrite(13, HIGH);  // 13.489589082528287
  delay(40);
  digitalWrite(13, LOW);
  delay(134);
  digitalWrite(13, HIGH);  // 13.663755823423942
  delay(40);
  digitalWrite(13, LOW);
  delay(128);
  digitalWrite(13, HIGH);  // 13.831672561655877
  delay(40);
  digitalWrite(13, LOW);
  delay(224);
  digitalWrite(13, HIGH);  // 14.095839340909095
  delay(40);
  digitalWrite(13, LOW);
  delay(104);
  digitalWrite(13, HIGH);  // 14.239797735596772
  delay(40);
  digitalWrite(13, LOW);
  delay(112);
  digitalWrite(13, HIGH);  // 14.391047800058788
  delay(40);
  digitalWrite(13, LOW);
  delay(3555);
  digitalWrite(13, HIGH);  // 17.986257665652467
  delay(40);
  digitalWrite(13, LOW);
  delay(76);
  digitalWrite(13, HIGH);  // 18.1029243820419
  delay(40);
  digitalWrite(13, LOW);
  delay(201);
  digitalWrite(13, HIGH);  // 18.343966151439353
  delay(40);
  digitalWrite(13, LOW);
  delay(91);
  digitalWrite(13, HIGH);  // 18.47438287368897
  delay(40);
  digitalWrite(13, LOW);
  delay(127);
  digitalWrite(13, HIGH);  // 18.64146627823241
  delay(40);
  digitalWrite(13, LOW);
  delay(180);
  digitalWrite(13, HIGH);  // 18.86125803857322
  delay(40);
  digitalWrite(13, LOW);
  delay(86);
  digitalWrite(13, HIGH);  // 18.987299758958233
  delay(40);
  digitalWrite(13, LOW);
  delay(85);
  digitalWrite(13, HIGH);  // 19.112924812499
  delay(40);
  digitalWrite(13, LOW);
  delay(476);
  digitalWrite(13, HIGH);  // 19.628758365677996
  delay(40);
  digitalWrite(13, LOW);
  delay(193);
  digitalWrite(13, HIGH);  // 19.86188346503474
  delay(40);
  digitalWrite(13, LOW);
  delay(142);
  digitalWrite(13, HIGH);  // 20.043758542548982
  delay(40);
  digitalWrite(13, LOW);
  delay(117);
  digitalWrite(13, HIGH);  // 20.20042527598622
  delay(40);
  digitalWrite(13, LOW);
  delay(113);
  digitalWrite(13, HIGH);  // 20.353550341247352
  delay(40);
  digitalWrite(13, LOW);
  delay(142);
  digitalWrite(13, HIGH);  // 20.53563375218372
  delay(40);
  digitalWrite(13, LOW);
  delay(213);
  digitalWrite(13, HIGH);  // 20.78896719348649
  delay(40);
  digitalWrite(13, LOW);
  delay(3731);
  digitalWrite(13, HIGH);  // 24.559802133930692
  delay(40);
  digitalWrite(13, LOW);
  delay(126);
  digitalWrite(13, HIGH);  // 24.72584387136351
  delay(40);
  digitalWrite(13, LOW);
  delay(71);
  digitalWrite(13, HIGH);  // 24.836885585355596
  delay(40);
  digitalWrite(13, LOW);
  delay(96);
  digitalWrite(13, HIGH);  // 24.97292731000256
  delay(40);
  digitalWrite(13, LOW);
  delay(133);
  digitalWrite(13, HIGH);  // 25.145635716943346
  delay(40);
  digitalWrite(13, LOW);
  delay(66);
  digitalWrite(13, HIGH);  // 25.251885762226582
  delay(40);
  digitalWrite(13, LOW);
  delay(69);
  digitalWrite(13, HIGH);  // 25.360219141731058
  delay(40);
  digitalWrite(13, LOW);
  delay(165);
  digitalWrite(13, HIGH);  // 25.565844229367432
  delay(40);
  digitalWrite(13, LOW);
  delay(73);
  digitalWrite(13, HIGH);  // 25.678760944158636
  delay(40);
  digitalWrite(13, LOW);
  delay(90);
  digitalWrite(13, HIGH);  // 25.808552666141882
  delay(40);
  digitalWrite(13, LOW);
  delay(70);
  digitalWrite(13, HIGH);  // 25.918344379601223
  delay(40);
  digitalWrite(13, LOW);
  delay(86);
  digitalWrite(13, HIGH);  // 26.044802766830482
  delay(40);
  digitalWrite(13, LOW);
  delay(124);
  digitalWrite(13, HIGH);  // 26.20896950346419
  delay(40);
  digitalWrite(13, LOW);
  delay(73);
  digitalWrite(13, HIGH);  // 26.32188621825539
  delay(40);
  digitalWrite(13, LOW);
  delay(144);
  digitalWrite(13, HIGH);  // 26.50584462999087
  delay(40);
  digitalWrite(13, LOW);
  delay(169);
  digitalWrite(13, HIGH);  // 26.71459471895911
  delay(40);
  digitalWrite(13, LOW);
  delay(144);
  digitalWrite(13, HIGH);  // 26.898136463850342
  delay(40);
  digitalWrite(13, LOW);
  delay(3804);
  digitalWrite(13, HIGH);  // 30.742721435726438
  delay(40);
  digitalWrite(13, LOW);
  delay(86);
  digitalWrite(13, HIGH);  // 30.8683464892672
  delay(40);
  digitalWrite(13, LOW);
  delay(473);
  digitalWrite(13, HIGH);  // 31.381888374802834
  delay(40);
  digitalWrite(13, LOW);
  delay(68);
  digitalWrite(13, HIGH);  // 31.48918008719669
  delay(40);
  digitalWrite(13, LOW);
  delay(68);
  digitalWrite(13, HIGH);  // 31.597513466701162
  delay(40);
  digitalWrite(13, LOW);
  delay(65);
  digitalWrite(13, HIGH);  // 31.70272184487378
  delay(40);
  digitalWrite(13, LOW);
  delay(163);
  digitalWrite(13, HIGH);  // 31.90563859802254
  delay(40);
  digitalWrite(13, LOW);
  delay(70);
  digitalWrite(13, HIGH);  // 32.01584697832613
  delay(40);
  digitalWrite(13, LOW);
  delay(186);
  digitalWrite(13, HIGH);  // 32.24126374106429
  delay(40);
  digitalWrite(13, LOW);
  delay(70);
  digitalWrite(13, HIGH);  // 32.35168045479001
  delay(40);
  digitalWrite(13, LOW);
  delay(1290);
  digitalWrite(13, HIGH);  // 33.68188935505167
  delay(40);
  digitalWrite(13, LOW);
  delay(95);
  digitalWrite(13, HIGH);  // 33.816681079165896
  delay(40);
  digitalWrite(13, LOW);
  delay(154);
  digitalWrite(13, HIGH);  // 34.01001449489696
  delay(40);
  digitalWrite(13, LOW);
  delay(114);
  digitalWrite(13, HIGH);  // 34.16438956069083
  delay(40);
  digitalWrite(13, LOW);
  delay(133);
  digitalWrite(13, HIGH);  // 34.33793130132011
  delay(40);
  digitalWrite(13, LOW);
  delay(66);
  digitalWrite(13, HIGH);  // 34.443556346336976
  delay(40);
  digitalWrite(13, LOW);
  delay(69);
  digitalWrite(13, HIGH);  // 34.55209805926358
  delay(40);
  digitalWrite(13, LOW);
  delay(93);
  digitalWrite(13, HIGH);  // 34.685223116000806
  delay(40);
  digitalWrite(13, LOW);
  delay(161);
  digitalWrite(13, HIGH);  // 34.88626486835045
  delay(40);
  digitalWrite(13, LOW);
  delay(133);
  digitalWrite(13, HIGH);  // 35.05938994213549
  delay(40);
  digitalWrite(13, LOW);
  delay(184);
  digitalWrite(13, HIGH);  // 35.28314003749665
  delay(40);
  digitalWrite(13, LOW);
  delay(109);
  digitalWrite(13, HIGH);  // 35.4329317680038
  delay(40);
  digitalWrite(13, LOW);
  delay(75);
  digitalWrite(13, HIGH);  // 35.547098483327744
  delay(40);
  digitalWrite(13, LOW);
  delay(167);
  digitalWrite(13, HIGH);  // 35.754181904918994
  delay(40);
  digitalWrite(13, LOW);
  delay(254);
  digitalWrite(13, HIGH);  // 36.04897369722443
  delay(40);
  digitalWrite(13, LOW);
  delay(66);
  digitalWrite(13, HIGH);  // 36.15418207539705
  delay(40);
  digitalWrite(13, LOW);
  delay(127);
  digitalWrite(13, HIGH);  // 36.321473813362616
  delay(40);
  digitalWrite(13, LOW);
  delay(201);
  digitalWrite(13, HIGH);  // 36.56272391618219
  delay(40);
  digitalWrite(13, LOW);
  delay(70);
  digitalWrite(13, HIGH);  // 36.67272396306366
  delay(40);
  digitalWrite(13, LOW);
  delay(135);
  digitalWrite(13, HIGH);  // 36.84772403764781
  delay(40);
  digitalWrite(13, LOW);
  delay(159);
  digitalWrite(13, HIGH);  // 37.0464741223541
  delay(40);
  digitalWrite(13, LOW);
  delay(67);
  digitalWrite(13, HIGH);  // 37.153140834481576
  delay(40);
  digitalWrite(13, LOW);
  delay(104);
  digitalWrite(13, HIGH);  // 37.29772422943562
  delay(40);
  digitalWrite(13, LOW);
  delay(72);
  digitalWrite(13, HIGH);  // 37.40959927711621
  delay(40);
  digitalWrite(13, LOW);
  delay(89);
  digitalWrite(13, HIGH);  // 37.53876599883308
  delay(40);
  digitalWrite(13, LOW);
  delay(104);
  digitalWrite(13, HIGH);  // 37.68230772667651
  delay(40);
  digitalWrite(13, LOW);
  delay(78);
  digitalWrite(13, HIGH);  // 37.800016110176564
  delay(40);
  digitalWrite(13, LOW);
  delay(68);
  digitalWrite(13, HIGH);  // 37.90876615652529
  delay(40);
  digitalWrite(13, LOW);
  delay(229);
  digitalWrite(13, HIGH);  // 38.17793293790948
  delay(40);
  digitalWrite(13, LOW);
  delay(85);
  digitalWrite(13, HIGH);  // 38.30272465776175
  delay(40);
  digitalWrite(13, LOW);
  delay(211);
  digitalWrite(13, HIGH);  // 38.55376643142115
  delay(40);
  digitalWrite(13, LOW);
  delay(181);
  digitalWrite(13, HIGH);  // 38.77480819229471
  delay(40);
  digitalWrite(13, LOW);
  delay(85);
  digitalWrite(13, HIGH);  // 38.8998082455691
  delay(40);
  digitalWrite(13, LOW);
  delay(224);
  digitalWrite(13, HIGH);  // 39.163350024555946
  delay(40);
  digitalWrite(13, LOW);
  delay(3159);
  digitalWrite(13, HIGH);  // 42.362518054691925
  delay(40);
  digitalWrite(13, LOW);
  delay(68);
  digitalWrite(13, HIGH);  // 42.470434767352145
  delay(40);
  digitalWrite(13, LOW);
  delay(125);
  digitalWrite(13, HIGH);  // 42.63564317109647
  delay(40);
  digitalWrite(13, LOW);
  delay(228);
  digitalWrite(13, HIGH);  // 42.90355995194792
  delay(40);
  digitalWrite(13, LOW);
  delay(66);
  digitalWrite(13, HIGH);  // 43.00980999723116
  delay(40);
  digitalWrite(13, LOW);
  delay(629);
  digitalWrite(13, HIGH);  // 43.67876861567129
  delay(40);
  digitalWrite(13, LOW);
  delay(139);
  digitalWrite(13, HIGH);  // 43.857935358697915
  delay(40);
  digitalWrite(13, LOW);
  delay(113);
  digitalWrite(13, HIGH);  // 44.0106437571148
  delay(40);
  digitalWrite(13, LOW);
  delay(71);
  digitalWrite(13, HIGH);  // 44.12189380452901
  delay(40);
  digitalWrite(13, LOW);
  delay(123);
  digitalWrite(13, HIGH);  // 44.28481054062997
  delay(40);
  digitalWrite(13, LOW);
  delay(87);
  digitalWrite(13, HIGH);  // 44.4110605944371
  delay(40);
  digitalWrite(13, LOW);
  delay(71);
  digitalWrite(13, HIGH);  // 44.52251897527344
  delay(40);
  digitalWrite(13, LOW);
  delay(195);
  digitalWrite(13, HIGH);  // 44.75772740885142
  delay(40);
  digitalWrite(13, LOW);
  delay(113);
  digitalWrite(13, HIGH);  // 44.91043580726831
  delay(40);
  digitalWrite(13, LOW);
  delay(85);
  digitalWrite(13, HIGH);  // 45.03501919369845
  delay(40);
  digitalWrite(13, LOW);
  delay(75);
  digitalWrite(13, HIGH);  // 45.15022757613302
  delay(40);
  digitalWrite(13, LOW);
  delay(158);
  digitalWrite(13, HIGH);  // 45.34876932741718
  delay(40);
  digitalWrite(13, LOW);
  delay(162);
  digitalWrite(13, HIGH);  // 45.55022774661108
  delay(40);
  digitalWrite(13, LOW);
  delay(156);
  digitalWrite(13, HIGH);  // 45.74689449709612
  delay(40);
  digitalWrite(13, LOW);
  delay(91);
  digitalWrite(13, HIGH);  // 45.87772788618999
  delay(40);
  digitalWrite(13, LOW);
  delay(118);
  digitalWrite(13, HIGH);  // 46.03564462015997
  delay(40);
  digitalWrite(13, LOW);
  delay(855);
  digitalWrite(13, HIGH);  // 46.930853335026754
  delay(40);
  digitalWrite(13, LOW);
  delay(157);
  digitalWrite(13, HIGH);  // 47.12710341866755
  delay(40);
  digitalWrite(13, LOW);
  delay(134);
  digitalWrite(13, HIGH);  // 47.30189515982958
  delay(40);
  digitalWrite(13, LOW);
  delay(89);
  digitalWrite(13, HIGH);  // 47.43002021443583
  delay(40);
  digitalWrite(13, LOW);
  delay(243);
  digitalWrite(13, HIGH);  // 47.71397866879083
  delay(40);
  digitalWrite(13, LOW);
  delay(82);
  digitalWrite(13, HIGH);  // 47.835437053889116
  delay(40);
  digitalWrite(13, LOW);
}