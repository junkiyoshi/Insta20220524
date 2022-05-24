#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(255);
	ofSetLineWidth(1);
	ofEnableDepthTest();

	ofTrueTypeFont font;
	font.loadFont("fonts/Kazesawa-Regular.ttf", 200, true, true, true);

	ofFbo fbo;
	fbo.allocate(ofGetWidth(), ofGetHeight());
	fbo.begin();
	ofClear(0);
	ofSetColor(0);

	string word = "PAC";
	font.drawString(word, ofGetWidth() * 0.5 - font.stringWidth(word) * 0.5, ofGetHeight() * 0.5 + font.stringHeight(word) * 0.5);

	fbo.end();
	ofPixels pixels;
	fbo.readToPixels(pixels);

	this->number_of_box = 1800;
	while (this->box_list.size() < this->number_of_box) {

		auto radius = this->box_list.size() < 110 ? ofRandom(5, 20) : ofRandom(2, 20);
		int x = ofRandom(0, 720);
		int y = ofRandom(0, 720);
		int z = ofRandom(-50, 50);

		ofColor color = pixels.getColor(x, y);
		if (color == ofColor(0, 0)) {

			continue;
		}

		auto tmp_location = glm::vec3(x - ofGetWindowWidth() * 0.5, y - ofGetWindowHeight() * 0.5, z);

		bool flag = true;
		for (int i = 0; i < this->box_list.size(); i++) {

			if (glm::distance(tmp_location, get<0>(this->box_list[i])) < get<1>(this->box_list[i]) + radius) {

				flag = false;
				break;
			}
		}

		if (flag) {

			auto size = (radius * 2) / sqrt(3);
			this->box_list.push_back(make_tuple(tmp_location, size));
		}
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(180);
	ofRotateY(sin(ofGetFrameNum() * 0.02) * 360);

	for (int i = 0; i < this->box_list.size(); i++) {

		auto location = get<0>(this->box_list[i]);
		auto size = get<1>(this->box_list[i]);

		ofPushMatrix();
		ofTranslate(location);

		ofRotateZ(ofRandom(360) + ofGetFrameNum() * ofRandom(1, 3));
		ofRotateY(ofRandom(360) + ofGetFrameNum() * ofRandom(1, 3));
		ofRotateX(ofRandom(360) + ofGetFrameNum() * ofRandom(1, 3));

		ofFill();
		ofSetColor(ofRandom(100, 255), ofRandom(100, 255), ofRandom(100, 255));
		ofDrawBox(size);

		ofNoFill();
		ofSetColor(255);
		ofDrawBox(size);

		ofPopMatrix();
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}