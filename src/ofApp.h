#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {

public:
	ofVec2f m_emptyPos;
	ofVec2f m_targetNotePos;
	ofVec2f m_mousePos;

	ofImage m_houseImage;
	ofVec2f m_housePos;

	ofImage m_manImage;
	ofVec2f m_manPos;
	float m_manAngle;

	ofImage m_milesImage;
	ofVec2f m_milesPos;
	float m_milesAngle;

	ofImage m_stairsImage;
	ofVec2f m_stairsPos;
	float m_stairsAngle;

	ofImage m_catImage;
	ofVec2f m_catPos;
	float m_catAngle;

	ofImage m_coinsImage;
	ofVec2f m_coinsPos;
	float m_coinsAngle;

	ofImage m_ratImage;
	ofVec2f m_ratPos;
	float m_ratAngle;

	ofImage m_note0;
	ofVec2f m_n0Pos;
	float m_n0Angle;

	ofImage m_note1;
	ofVec2f m_n1Pos;
	float m_n1Angle;

	ofImage m_note2;
	ofVec2f m_n2Pos;
	float m_n2Angle;

	void setup();
	void update();
	void draw();

	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);

	//the function to push & pop matrix and draw image which include the satellitesPos function inside
	void matrix(ofVec2f main, ofVec2f sat, float worldAngle, float selfAngle, ofImage satImg);

	//the function used for tranlaste, scale and rotate images
	void satellitesPos(ofVec2f main, ofVec2f sat, float angle1, float angle2, float scale);

	float lerp(float start, float end, float percent);
};
