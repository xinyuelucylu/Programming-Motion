#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	//set the window
	ofSetWindowShape(1000, 800);
	ofSetBackgroundColor(40, 0, 0, 50);

	// load images
	m_houseImage.load("house.png");
	m_catImage.load("cat.png");
	m_coinsImage.load("coins.png");
	m_manImage.load("man.png");
	m_milesImage.load("miles.png");
	m_ratImage.load("mouse.png");
	m_stairsImage.load("stairs.png");
	m_note0.load("note0.png");
	m_note1.load("note1.png");
	m_note2.load("note2.png");

	//set position of all object
	m_housePos.set(ofGetWindowWidth() / 2.0f, ofGetWindowHeight() / 2.0f);
	m_manPos.set(0.0f, -180.0f);
	m_catPos.set(300.0f, 100.0f);
	m_milesPos.set(0.0f, 240.0f);
	m_stairsPos.set(-240.0f, 0.0f);
	m_ratPos.set(0.0f, -300.0f);
	m_coinsPos.set(150.0f, 0.0f);

	m_n0Pos.set(400.0f, 200.0f);
	m_n1Pos.set(-120.0f, 0.0f);
	m_n2Pos.set(-300.0f, 0.0f);

	//set position of other invisible objects
	m_emptyPos.set(0.0f, 0.0f);
	m_targetNotePos.set(m_n0Pos.x, m_n0Pos.y);
	m_mousePos.set(0.0f, 0.0f);

	//set angles of objects
	m_manAngle = m_catAngle = m_milesAngle = m_stairsAngle = m_ratAngle = m_coinsAngle = 0.0f;

	//set global anchor point
	ofSetRectMode(OF_RECTMODE_CENTER);
}

//--------------------------------------------------------------
void ofApp::update() {
	//angles update
	m_manAngle += 0.6;
	m_catAngle += 0.8;
	m_milesAngle += 0.02;
	m_stairsAngle += -0.1;

	m_ratAngle += 0.8;
	m_coinsAngle += -0.5;

	//update the condition of objects following the mouse
	m_mousePos.set((float)ofGetMouseX(), (float)ofGetMouseY());

	m_n0Pos.x = lerp(m_n0Pos.x, m_targetNotePos.x, 0.1f);
	m_n0Pos.y = lerp(m_n0Pos.y, m_targetNotePos.y, 0.1f);

	ofVec2f vecToMouse = m_mousePos - m_n0Pos;
	m_n0Angle = ofRadToDeg(atan2(vecToMouse.y, vecToMouse.x));

	ofVec2f vecToN0 = m_targetNotePos - m_n0Pos;
	m_n1Angle = ofRadToDeg(atan2(vecToN0.y, vecToN0.x));
}

//--------------------------------------------------------------
void ofApp::draw() {
	/*--------------objects orbiting-------------*/
	//house is located at the centre
	matrix(m_housePos, m_emptyPos, 0, 0, m_houseImage);

	//miles and stairs orbit around house
	matrix(m_housePos, m_milesPos, m_milesAngle, 0, m_milesImage);
	matrix(m_housePos, m_stairsPos, m_stairsAngle, -m_stairsAngle, m_stairsImage);

	//coins orbit around the stairs
	ofPushMatrix();
	satellitesPos(m_housePos, m_stairsPos, m_stairsAngle, -m_stairsAngle, 0.3f);
	satellitesPos(m_emptyPos, -m_coinsPos, m_coinsAngle, -m_coinsAngle, 1.0f);
	m_coinsImage.draw(0, 0);
	ofPopMatrix();

	//cat orbits around house
	matrix(m_housePos, m_catPos, m_catAngle, -m_catAngle, m_catImage);

	//rat orbit around cat (cat chasing rat)
	ofPushMatrix();
	satellitesPos(m_housePos, m_catPos, m_catAngle, 0, 0.35f);
	satellitesPos(m_emptyPos, -m_ratPos, 0, -m_ratAngle, 1.0f);
	m_ratImage.draw(0, 0);
	ofPopMatrix();

	//man orbits around house
	matrix(m_housePos, m_manPos, -m_manAngle, m_manAngle, m_manImage);

	/*--------------objects interact with mouse-------------*/
	//note0 is facing and fly toward the mouse
	matrix(m_n0Pos, m_emptyPos, m_n0Angle, 0, m_note0);

	//note1 & note2 are following note0, they only face towards the mouse by clicking!!
	ofPushMatrix();
	satellitesPos(m_n0Pos, m_emptyPos, 0, m_n0Angle, 0.4f);
	satellitesPos(m_n1Pos, m_emptyPos, -m_n0Angle, m_n1Angle, 1.0f);
	m_note1.draw(0, 0);
	satellitesPos(-m_n1Pos, m_n2Pos, 0, 0, 1.0f);
	m_note2.draw(0, 0);
	ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
	if (button == OF_MOUSE_BUTTON_LEFT) {
		m_targetNotePos.set((float)x, (float)y);
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	m_targetNotePos.set((float)x, (float)y);
}

//--------------------------------------------------------------
void ofApp::matrix(ofVec2f main, ofVec2f sat, float worldAngle, float selfAngle, ofImage satImg) {
	ofPushMatrix();
	satellitesPos(main, sat, worldAngle, selfAngle, 0.35f);
	satImg.draw(0, 0);
	ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::satellitesPos(ofVec2f main, ofVec2f sat, float worldAngle, float selfAngle, float scale) {
	ofTranslate(main);
	ofRotate(worldAngle);
	ofTranslate(sat);
	ofScale(scale, scale);
	ofRotate(selfAngle);
}

//--------------------------------------------------------------
float ofApp::lerp(float start, float end, float percent) {
	return (start + percent * (end - start));
}
