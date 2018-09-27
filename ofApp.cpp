#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {
	
	this->cam.begin();

	for (int g = 0; g < 8; g++) {

		ofPoint parent_seed = ofPoint(ofRandom(100), ofRandom(100), ofRandom(100));
		vector<ofPoint> parent_log;

		int number_of_child = 30;
		vector<ofPoint> child_seeds;
		vector<ofColor> child_colors;
		vector<vector<ofPoint>> child_logs;
		for (int i = 0; i < number_of_child; i++) {

			ofPoint child_seed = ofPoint(ofRandom(100), ofRandom(100), ofRandom(100));
			child_seeds.push_back(child_seed);

			ofColor child_color;
			child_color.setHsb(ofRandom(255), 200, 255);
			child_colors.push_back(child_color);

			vector<ofPoint> child_log;
			child_logs.push_back(child_log);
		}

		for (int l = 0; l < 30; l++) {

			float x = ofMap(ofNoise(parent_seed.x, (ofGetFrameNum() + l) * 0.005), 0, 1, ofGetWidth() * -0.5, ofGetWidth() * 0.5);
			float y = ofMap(ofNoise(parent_seed.y, (ofGetFrameNum() + l) * 0.005), 0, 1, ofGetHeight() * -0.5, ofGetHeight() * 0.5);
			float z = ofMap(ofNoise(parent_seed.z, (ofGetFrameNum() + l) * 0.005), 0, 1, ofGetWidth() > ofGetHeight() ? ofGetHeight() : ofGetWidth() * -0.5, ofGetWidth() > ofGetHeight() ? ofGetHeight() : ofGetWidth() * 0.5);

			ofPoint parent_point = ofPoint(x, y, z);
			parent_log.push_back(parent_point);

			for (int i = 0; i < number_of_child; i++) {

				x = ofMap(ofNoise(child_seeds[i].x, (ofGetFrameNum() + l) * 0.005), 0, 1, -50, 50);
				y = ofMap(ofNoise(child_seeds[i].y, (ofGetFrameNum() + l) * 0.005), 0, 1, -50, 50);
				z = ofMap(ofNoise(child_seeds[i].z, (ofGetFrameNum() + l) * 0.005), 0, 1, -50, 50);

				ofPoint child_point = parent_point + ofPoint(x, y, z);
				child_logs[i].push_back(child_point);
			}
		}

		ofSetColor(239);
		ofFill();
		ofDrawSphere(parent_log[parent_log.size() - 1], 10);
		
		for (int i = 0; i < number_of_child; i++) {

			for (int l = 0; l < child_logs[i].size() - 1; l++) {

				ofSetColor(child_colors[i], ofMap(l, 0, child_logs[i].size(), 1, 255));
				ofDrawLine(child_logs[i][l], child_logs[i][l + 1]);
			}

			ofFill();
			ofDrawSphere(child_logs[i][child_logs[i].size() - 1], 5);
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}