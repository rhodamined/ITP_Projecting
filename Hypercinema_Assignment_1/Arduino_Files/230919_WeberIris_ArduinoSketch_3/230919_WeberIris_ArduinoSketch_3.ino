// September 1, 2023
// 2:04PM
// Weber & Iris on separate solenoids
// Prominence Weber = 1000 -- variances is crazy higher -- if i knew enough about compression I'd have compressed it more
// Prominence Iris = 500
// - record speech
// - reading wave form in python (native python wave module)
// - identifying wave peaks using python (wav_plot.py, using scipy)
// - use python to spit out arduino code for timestamps (wav_plot.py)
// * Has successfully been used with Nano 33 IOT to fire a 12V solenoid
// * Solenoid circuiting adapter from: https://www.makerguides.com/control-a-solenoid-with-arduino/


void setup() {
  pinMode(13, OUTPUT);    // IRIS
  pinMode(12, OUTPUT);    // WEBER
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
}

void loop() {

delay(799);
digitalWrite(13, HIGH);  // 0.819166895306688	WEBER
delay(20);
digitalWrite(13, LOW);
delay(337);
digitalWrite(13, HIGH);  // 1.176458661698084	WEBER
delay(20);
digitalWrite(13, LOW);
delay(303);
digitalWrite(13, HIGH);  // 1.4995837518864548	WEBER
delay(20);
digitalWrite(13, LOW);
delay(200);
digitalWrite(13, HIGH);  // 1.7193754798998209	WEBER
delay(20);
digitalWrite(13, LOW);
delay(296);
digitalWrite(13, HIGH);  // 2.035417234777808	WEBER
delay(20);
digitalWrite(13, LOW);
delay(1288);
digitalWrite(12, HIGH);  // 3.3431259331094663	IRIS
delay(20);
digitalWrite(12, LOW);
delay(212);
digitalWrite(12, HIGH);  // 3.5756259980032263	IRIS
delay(20);
digitalWrite(12, LOW);
delay(391);
digitalWrite(12, HIGH);  // 3.9862511126139792	IRIS
delay(20);
digitalWrite(12, LOW);
delay(286);
digitalWrite(12, HIGH);  // 4.292709531483801	IRIS
delay(20);
digitalWrite(12, LOW);
delay(383);
digitalWrite(12, HIGH);  // 4.69500131043528	IRIS
delay(20);
digitalWrite(12, LOW);
delay(315);
digitalWrite(12, HIGH);  // 5.030834737504044	IRIS
delay(20);
digitalWrite(12, LOW);
delay(203);
digitalWrite(12, HIGH);  // 5.253751466389638	IRIS
delay(20);
digitalWrite(12, LOW);
delay(555);
digitalWrite(12, HIGH);  // 5.828959960271064	IRIS
delay(20);
digitalWrite(12, LOW);
delay(409);
digitalWrite(12, HIGH);  // 6.2575017465492575	IRIS
delay(20);
digitalWrite(12, LOW);
delay(653);
digitalWrite(12, HIGH);  // 6.930626934427159	IRIS
delay(20);
digitalWrite(12, LOW);
delay(1094);
digitalWrite(12, HIGH);  // 8.044585578680683	IRIS
delay(20);
digitalWrite(12, LOW);
delay(267);
digitalWrite(12, HIGH);  // 8.331668992142692	IRIS
delay(20);
digitalWrite(12, LOW);
delay(702);
digitalWrite(12, HIGH);  // 9.053960860410314	IRIS
delay(20);
digitalWrite(12, LOW);
delay(190);
digitalWrite(12, HIGH);  // 9.263335918849586	IRIS
delay(20);
digitalWrite(12, LOW);
delay(283);
digitalWrite(12, HIGH);  // 9.566252670064216	IRIS
delay(20);
digitalWrite(12, LOW);
delay(375);
digitalWrite(12, HIGH);  // 9.96125278031383	IRIS
delay(20);
digitalWrite(12, LOW);
delay(1400);
digitalWrite(13, HIGH);  // 11.381253176654212	WEBER
delay(20);
digitalWrite(13, LOW);
delay(756);
digitalWrite(13, HIGH);  // 12.157711726707118	WEBER
delay(20);
digitalWrite(13, LOW);
delay(208);
digitalWrite(13, HIGH);  // 12.385211790205313	WEBER
delay(20);
digitalWrite(13, LOW);
delay(227);
digitalWrite(13, HIGH);  // 12.632920192677249	WEBER
delay(20);
digitalWrite(13, LOW);
delay(366);
digitalWrite(13, HIGH);  // 13.018128633527215	WEBER
delay(20);
digitalWrite(13, LOW);
delay(259);
digitalWrite(13, HIGH);  // 13.297712044895876	WEBER
delay(20);
digitalWrite(13, LOW);
delay(290);
digitalWrite(13, HIGH);  // 13.607295464637925	WEBER
delay(20);
digitalWrite(13, LOW);
delay(212);
digitalWrite(13, HIGH);  // 13.839795529531685	WEBER
delay(20);
digitalWrite(13, LOW);
delay(348);
digitalWrite(13, HIGH);  // 14.20708729871421	WEBER
delay(20);
digitalWrite(13, LOW);
delay(192);
digitalWrite(13, HIGH);  // 14.41937902463423	WEBER
delay(20);
digitalWrite(13, LOW);
delay(250);
digitalWrite(13, HIGH);  // 14.689795766777689	WEBER
delay(20);
digitalWrite(13, LOW);
delay(196);
digitalWrite(13, HIGH);  // 14.905004160178454	WEBER
delay(20);
digitalWrite(13, LOW);
delay(358);
digitalWrite(13, HIGH);  // 15.283129265718037	WEBER
delay(20);
digitalWrite(13, LOW);
delay(330);
digitalWrite(13, HIGH);  // 15.633546030190532	WEBER
delay(20);
digitalWrite(13, LOW);
delay(189);
digitalWrite(13, HIGH);  // 15.842087755063877	WEBER
delay(20);
digitalWrite(13, LOW);
delay(202);
digitalWrite(13, HIGH);  // 16.064171150383544	WEBER
delay(20);
digitalWrite(13, LOW);
delay(1337);
digitalWrite(12, HIGH);  // 17.421254862496404	IRIS
delay(20);
digitalWrite(12, LOW);
delay(189);
digitalWrite(12, HIGH);  // 17.630421587544195	IRIS
delay(20);
digitalWrite(12, LOW);
delay(509);
digitalWrite(12, HIGH);  // 18.15979673529961	IRIS
delay(20);
digitalWrite(12, LOW);
delay(268);
digitalWrite(12, HIGH);  // 18.4470884821531	IRIS
delay(20);
digitalWrite(12, LOW);
delay(379);
digitalWrite(12, HIGH);  // 18.846671927015315	IRIS
delay(20);
digitalWrite(12, LOW);
delay(635);
digitalWrite(12, HIGH);  // 19.501047109659847	IRIS
delay(20);
digitalWrite(12, LOW);
delay(317);
digitalWrite(12, HIGH);  // 19.838130537077504	IRIS
delay(20);
digitalWrite(12, LOW);
delay(426);
digitalWrite(12, HIGH);  // 20.284172328240174	IRIS
delay(20);
digitalWrite(12, LOW);
delay(265);
digitalWrite(12, HIGH);  // 20.569380741178847	IRIS
delay(20);
digitalWrite(12, LOW);
delay(413);
digitalWrite(12, HIGH);  // 21.002922528852604	IRIS
delay(20);
digitalWrite(12, LOW);
delay(349);
digitalWrite(12, HIGH);  // 21.37146429838402	IRIS
delay(20);
digitalWrite(12, LOW);
delay(419);
digitalWrite(12, HIGH);  // 21.810006087453345	IRIS
delay(20);
digitalWrite(12, LOW);
delay(269);
digitalWrite(12, HIGH);  // 22.099589501613135	IRIS
delay(20);
digitalWrite(12, LOW);
delay(191);
digitalWrite(12, HIGH);  // 22.310839560575744	IRIS
delay(20);
digitalWrite(12, LOW);
delay(561);
digitalWrite(12, HIGH);  // 22.8914647226357	IRIS
delay(20);
digitalWrite(12, LOW);
delay(626);
digitalWrite(12, HIGH);  // 23.537089902837995	IRIS
delay(20);
digitalWrite(12, LOW);
delay(307);
digitalWrite(12, HIGH);  // 23.864589994247485	IRIS
delay(20);
digitalWrite(12, LOW);
delay(631);
digitalWrite(12, HIGH);  // 24.51500684245386	IRIS
delay(20);
digitalWrite(12, LOW);
delay(188);
digitalWrite(12, HIGH);  // 24.72375690071869	IRIS
delay(20);
digitalWrite(12, LOW);
delay(1227);
digitalWrite(12, HIGH);  // 25.970632248737644	IRIS
delay(20);
digitalWrite(12, LOW);
delay(212);
digitalWrite(12, HIGH);  // 26.20292398023992	IRIS
delay(20);
digitalWrite(12, LOW);
delay(275);
digitalWrite(12, HIGH);  // 26.49771572918676	IRIS
delay(20);
digitalWrite(12, LOW);
delay(234);
digitalWrite(12, HIGH);  // 26.751049133228705	IRIS
delay(20);
digitalWrite(12, LOW);
delay(210);
digitalWrite(12, HIGH);  // 26.98188253099061	IRIS
delay(20);
digitalWrite(12, LOW);
delay(293);
digitalWrite(12, HIGH);  // 27.294590951604885	IRIS
delay(20);
digitalWrite(12, LOW);
delay(338);
digitalWrite(12, HIGH);  // 27.652507718170728	IRIS
delay(20);
digitalWrite(12, LOW);
delay(794);
digitalWrite(12, HIGH);  // 28.46646627869037	IRIS
delay(20);
digitalWrite(12, LOW);
delay(577);
digitalWrite(12, HIGH);  // 29.06354977867739	IRIS
delay(20);
digitalWrite(12, LOW);
delay(198);
digitalWrite(12, HIGH);  // 29.281674839558903	IRIS
delay(20);
digitalWrite(12, LOW);
delay(475);
digitalWrite(12, HIGH);  // 29.77646664432833	IRIS
delay(20);
digitalWrite(12, LOW);
delay(317);
digitalWrite(12, HIGH);  // 30.113550071745983	IRIS
delay(20);
digitalWrite(12, LOW);
delay(202);
digitalWrite(12, HIGH);  // 30.335216800282687	IRIS
delay(20);
digitalWrite(12, LOW);
delay(421);
digitalWrite(12, HIGH);  // 30.776050256658312	IRIS
delay(20);
digitalWrite(12, LOW);
delay(713);
digitalWrite(12, HIGH);  // 31.50917546128299	IRIS
delay(20);
digitalWrite(12, LOW);
delay(484);
digitalWrite(12, HIGH);  // 32.0133422686691	IRIS
delay(20);
digitalWrite(12, LOW);
delay(205);
digitalWrite(12, HIGH);  // 32.238967331643956	IRIS
delay(20);
digitalWrite(12, LOW);
delay(996);
digitalWrite(13, HIGH);  // 33.25438428172656	WEBER
delay(20);
digitalWrite(13, LOW);
delay(201);
digitalWrite(13, HIGH);  // 33.47500934330586	WEBER
delay(20);
digitalWrite(13, LOW);
delay(1235);
digitalWrite(13, HIGH);  // 34.73021802698408	WEBER
delay(20);
digitalWrite(13, LOW);
delay(323);
digitalWrite(13, HIGH);  // 35.07355145614619	WEBER
delay(20);
digitalWrite(13, LOW);
delay(233);
digitalWrite(13, HIGH);  // 35.32646819340518	WEBER
delay(20);
digitalWrite(13, LOW);
delay(280);
digitalWrite(13, HIGH);  // 35.62625994374758	WEBER
delay(20);
digitalWrite(13, LOW);
delay(208);
digitalWrite(13, HIGH);  // 35.85480167420318	WEBER
delay(20);
digitalWrite(13, LOW);
delay(619);
digitalWrite(13, HIGH);  // 36.493135185703615	WEBER
delay(20);
digitalWrite(13, LOW);
delay(311);
digitalWrite(13, HIGH);  // 36.824385278159774	WEBER
delay(20);
digitalWrite(13, LOW);
delay(197);
digitalWrite(13, HIGH);  // 37.04167700547536	WEBER
delay(20);
digitalWrite(13, LOW);
delay(191);
digitalWrite(13, HIGH);  // 37.25251039765501	WEBER
delay(20);
digitalWrite(13, LOW);
delay(194);
digitalWrite(13, HIGH);  // 37.466885457489845	WEBER
delay(20);
digitalWrite(13, LOW);
delay(333);
digitalWrite(13, HIGH);  // 37.819385555877155	WEBER
delay(20);
digitalWrite(13, LOW);
delay(189);
digitalWrite(13, HIGH);  // 38.02813561414199	WEBER
delay(20);
digitalWrite(13, LOW);
delay(1442);
digitalWrite(12, HIGH);  // 39.490219355561706	IRIS
delay(20);
digitalWrite(12, LOW);
delay(610);
digitalWrite(12, HIGH);  // 40.120011198011376	IRIS
delay(20);
digitalWrite(12, LOW);
delay(525);
digitalWrite(12, HIGH);  // 40.66521968351942	IRIS
delay(20);
digitalWrite(12, LOW);
delay(621);
digitalWrite(12, HIGH);  // 41.30626152910911	IRIS
delay(20);
digitalWrite(12, LOW);
delay(323);
digitalWrite(12, HIGH);  // 41.64959495827122	IRIS
delay(20);
digitalWrite(12, LOW);
delay(315);
digitalWrite(12, HIGH);  // 41.98480338516554	IRIS
delay(20);
digitalWrite(12, LOW);
delay(1956);
digitalWrite(13, HIGH);  // 43.96001226980509	WEBER
delay(20);
digitalWrite(13, LOW);
delay(630);
digitalWrite(13, HIGH);  // 44.61042911801147	WEBER
delay(20);
digitalWrite(13, LOW);
delay(261);
digitalWrite(13, HIGH);  // 44.89167919651199	WEBER
delay(20);
digitalWrite(13, LOW);
delay(382);
digitalWrite(13, HIGH);  // 45.2935543086805	WEBER
delay(20);
digitalWrite(13, LOW);
delay(238);
digitalWrite(13, HIGH);  // 45.55105438055208	WEBER
delay(20);
digitalWrite(13, LOW);
delay(221);
digitalWrite(13, HIGH);  // 45.792721114671046	WEBER
delay(20);
digitalWrite(13, LOW);
delay(379);
digitalWrite(13, HIGH);  // 46.191471225967334	WEBER
delay(20);
digitalWrite(13, LOW);
delay(904);
digitalWrite(13, HIGH);  // 47.11584648397236	WEBER
delay(20);
digitalWrite(13, LOW);
delay(242);
digitalWrite(13, HIGH);  // 47.377721557065065	WEBER
delay(20);
digitalWrite(13, LOW);
delay(224);
digitalWrite(13, HIGH);  // 47.62105495831588	WEBER
delay(20);
digitalWrite(13, LOW);
delay(196);
digitalWrite(13, HIGH);  // 47.83730501867405	WEBER
delay(20);
digitalWrite(13, LOW);
delay(214);
digitalWrite(13, HIGH);  // 48.071055083916704	WEBER
delay(20);
digitalWrite(13, LOW);
delay(283);
digitalWrite(13, HIGH);  // 48.37459683530578	WEBER
delay(20);
digitalWrite(13, LOW);
delay(309);
digitalWrite(13, HIGH);  // 48.703555260455644	WEBER
delay(20);
digitalWrite(13, LOW);
delay(204);
digitalWrite(13, HIGH);  // 48.92793032308161	WEBER
delay(20);
digitalWrite(13, LOW);
delay(223);
digitalWrite(13, HIGH);  // 49.17022205737502	WEBER
delay(20);
digitalWrite(13, LOW);
delay(1434);
digitalWrite(13, HIGH);  // 50.62438912991843	WEBER
delay(20);
digitalWrite(13, LOW);
delay(298);
digitalWrite(13, HIGH);  // 50.94251421871123	WEBER
delay(20);
digitalWrite(13, LOW);
delay(294);
digitalWrite(13, HIGH);  // 51.25688930645737	WEBER
delay(20);
digitalWrite(13, LOW);
delay(223);
digitalWrite(13, HIGH);  // 51.499806040925215	WEBER
delay(20);
digitalWrite(13, LOW);
delay(201);
digitalWrite(13, HIGH);  // 51.72043110250451	WEBER
delay(20);
digitalWrite(13, LOW);
delay(197);
digitalWrite(13, HIGH);  // 51.93751449642861	WEBER
delay(20);
digitalWrite(13, LOW);
delay(294);
digitalWrite(13, HIGH);  // 52.251264584000296	WEBER
delay(20);
digitalWrite(13, LOW);
delay(191);
digitalWrite(13, HIGH);  // 52.46272297635439	WEBER
delay(20);
digitalWrite(13, LOW);
delay(207);
digitalWrite(13, HIGH);  // 52.68959803967814	WEBER
delay(20);
digitalWrite(13, LOW);
delay(284);
digitalWrite(13, HIGH);  // 52.9933481244587	WEBER
delay(20);
digitalWrite(13, LOW);
delay(398);
digitalWrite(13, HIGH);  // 53.411473241162795	WEBER
delay(20);
digitalWrite(13, LOW);
delay(800);
digitalWrite(13, HIGH);  // 54.23189013681838	WEBER
delay(20);
digitalWrite(13, LOW);
delay(230);
digitalWrite(13, HIGH);  // 54.481265206422165	WEBER
delay(20);
digitalWrite(13, LOW);
delay(190);
digitalWrite(13, HIGH);  // 54.69126526503589	WEBER
delay(20);
digitalWrite(13, LOW);
delay(235);
digitalWrite(13, HIGH);  // 54.946265336209684	WEBER
delay(20);
digitalWrite(13, LOW);
delay(212);
digitalWrite(13, HIGH);  // 55.178140400929	WEBER
delay(20);
digitalWrite(13, LOW);
delay(235);
digitalWrite(13, HIGH);  // 55.43397380566873	WEBER
delay(20);
digitalWrite(13, LOW);
delay(200);
digitalWrite(13, HIGH);  // 55.65314053350765	WEBER
delay(20);
digitalWrite(13, LOW);
delay(388);
digitalWrite(13, HIGH);  // 56.06126564742062	WEBER
delay(20);
digitalWrite(13, LOW);
delay(194);
digitalWrite(13, HIGH);  // 56.275224040472494	WEBER
delay(20);
digitalWrite(13, LOW);
delay(1490);
digitalWrite(13, HIGH);  // 57.78564112871601	WEBER
delay(20);
digitalWrite(13, LOW);
delay(283);
digitalWrite(13, HIGH);  // 58.08855787993064	WEBER
delay(20);
digitalWrite(13, LOW);
delay(333);
digitalWrite(13, HIGH);  // 58.44189131188388	WEBER
delay(20);
digitalWrite(13, LOW);
delay(397);
digitalWrite(13, HIGH);  // 58.85814142806464	WEBER
delay(20);
digitalWrite(13, LOW);
delay(340);
digitalWrite(13, HIGH);  // 59.218558195328264	WEBER
delay(20);
digitalWrite(13, LOW);
delay(1358);
digitalWrite(12, HIGH);  // 60.59626691319783	IRIS
delay(20);
digitalWrite(12, LOW);
delay(191);
digitalWrite(12, HIGH);  // 60.80751697216044	IRIS
delay(20);
digitalWrite(12, LOW);
delay(535);
digitalWrite(12, HIGH);  // 61.36272546045961	IRIS
delay(20);
digitalWrite(12, LOW);
delay(1251);
digitalWrite(13, HIGH);  // 62.633975815281936	WEBER
delay(20);
digitalWrite(13, LOW);
delay(212);
digitalWrite(13, HIGH);  // 62.865850880001254	WEBER
delay(20);
digitalWrite(13, LOW);
delay(201);
digitalWrite(13, HIGH);  // 63.086059274797584	WEBER
delay(20);
digitalWrite(13, LOW);
delay(407);
digitalWrite(13, HIGH);  // 63.513142727335406	WEBER
delay(20);
digitalWrite(13, LOW);
delay(254);
digitalWrite(13, HIGH);  // 63.7877261373085	WEBER
delay(20);
digitalWrite(13, LOW);
delay(225);
digitalWrite(13, HIGH);  // 64.03210120551672	WEBER
delay(20);
digitalWrite(13, LOW);
delay(194);
digitalWrite(13, HIGH);  // 64.24668459874304	WEBER
delay(20);
digitalWrite(13, LOW);
delay(1412);
digitalWrite(13, HIGH);  // 65.67814333161493	WEBER
delay(20);
digitalWrite(13, LOW);
delay(309);
digitalWrite(13, HIGH);  // 66.00751842354775	WEBER
delay(20);
digitalWrite(13, LOW);
delay(189);
digitalWrite(13, HIGH);  // 66.21626848181259	WEBER
delay(20);
digitalWrite(13, LOW);
delay(294);
digitalWrite(13, HIGH);  // 66.53043523616724	WEBER
delay(20);
digitalWrite(13, LOW);
delay(194);
digitalWrite(13, HIGH);  // 66.74418529582763	WEBER
delay(20);
digitalWrite(13, LOW);
delay(242);
digitalWrite(13, HIGH);  // 67.00606036892033	WEBER
delay(20);
digitalWrite(13, LOW);
delay(284);
digitalWrite(13, HIGH);  // 67.31001878709237	WEBER
delay(20);
digitalWrite(13, LOW);
delay(243);
digitalWrite(13, HIGH);  // 67.57314386053396	WEBER
delay(20);
digitalWrite(13, LOW);
delay(267);
digitalWrite(13, HIGH);  // 67.86022727399597	WEBER
delay(20);
digitalWrite(13, LOW);
delay(594);
digitalWrite(13, HIGH);  // 68.47439411208451	WEBER
delay(20);
digitalWrite(13, LOW);
delay(304);
digitalWrite(13, HIGH);  // 68.79856086923029	WEBER
delay(20);
digitalWrite(13, LOW);
delay(227);
digitalWrite(13, HIGH);  // 69.0454359381363	WEBER
delay(20);
digitalWrite(13, LOW);
delay(386);
digitalWrite(13, HIGH);  // 69.45189438491741	WEBER
delay(20);
digitalWrite(13, LOW);
delay(193);
digitalWrite(13, HIGH);  // 69.6643944442289	WEBER
delay(20);
digitalWrite(13, LOW);
delay(209);
digitalWrite(13, HIGH);  // 69.89335284146748	WEBER
delay(20);
digitalWrite(13, LOW);
delay(381);
digitalWrite(13, HIGH);  // 70.29460295346155	WEBER
delay(20);
digitalWrite(13, LOW);
delay(497);
digitalWrite(13, HIGH);  // 70.81189476451101	WEBER
delay(20);
digitalWrite(13, LOW);
delay(206);
digitalWrite(13, HIGH);  // 71.03772816087735	WEBER
delay(20);
digitalWrite(13, LOW);
delay(1065);
digitalWrite(12, HIGH);  // 72.12293679710638	IRIS
delay(20);
digitalWrite(12, LOW);
delay(214);
digitalWrite(12, HIGH);  // 72.35689519574052	IRIS
delay(20);
digitalWrite(12, LOW);
delay(599);
digitalWrite(12, HIGH);  // 72.97502036826721	IRIS
delay(20);
digitalWrite(12, LOW);
delay(352);
digitalWrite(12, HIGH);  // 73.34752047223678	IRIS
delay(20);
digitalWrite(12, LOW);
delay(224);
digitalWrite(12, HIGH);  // 73.59189554044501	IRIS
delay(20);
digitalWrite(12, LOW);
delay(190);
digitalWrite(12, HIGH);  // 73.80127059888427	IRIS
delay(20);
digitalWrite(12, LOW);
delay(5000);

}
