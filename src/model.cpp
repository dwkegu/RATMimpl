﻿/*
 * Copyright (C) 2007 by
 * 
 * 	Xuan-Hieu Phan
 *	hieuxuan@ecei.tohoku.ac.jp or pxhieu@gmail.com
 * 	Graduate School of Information Sciences
 * 	Tohoku University
 *
 * GibbsLDA++ is a free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 2 of the License,
 * or (at your option) any later version.
 *
 * GibbsLDA++ is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GibbsLDA++; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
 */

/* 
 * References:
 * + The Java code of Gregor Heinrich (gregor@arbylon.net)
 *   http://www.arbylon.net/projects/LdaGibbsSampler.java
 * + "Parameter estimation for text analysis" by Gregor Heinrich
 *   http://www.arbylon.net/publications/text-est.pdf
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "constants.h"
#include "strtokenizer.h"
#include "utils.h"
#include "dataset.h"
#include "model.h"

using namespace std;

model::~model() {
    if (p1) {
		delete p2;
    }
	if (p2) {
		delete p2;
	}

    if (ptrndata) {
	delete ptrndata;
    }
    
    if (pnewdata) {
	delete pnewdata;
    }

    if (z) {
		for (int m = 0; m < M; m++) {
			if (z[m]) {
				delete []z[m];
			}
		}
		delete[] z;
    }
    
    if (nw) {
	for (int w = 0; w < V; w++) {
	    if (nw[w]) {
			delete nw[w];
	    }
	}
    }

    if (nd) {
		for (int m = 0; m < M; m++) {
			if (nd[m]) {
			delete []nd[m];
			}
		}
		delete[] nd;
    } 
	if (nds) {
		for (int m = 0; m < M; m++) {
			if (nds[m]) {
				for (int s = 0; s < Sd[m]; s++) {
					if (nds[m]) {
						delete[] nds[m][s];
					}
				}
				delete[] nds[m];
			}
		}
		delete[] nds;
	}
    if (nwsum) {
		delete[] nwsum;
    }   
    
    if (ndsum) {
		delete[] ndsum;
    }
	if (ndssum) {
		for (int m = 0; m < M; m++) {
			if (ndssum[m]) {
				delete[] ndssum[m];
			}
		}
		delete[] ndssum;
	}
	if (ndsc) {
		for (int m = 0; m < M; m++) {
			if (ndsc[m]) {
				for (int s = 0; s < Sd[m]; s++) {
					if (ndsc[m][s]) {
						delete[] ndsc[m][s];
					}
				}
				delete[] ndsc[m];
			}
		}
		delete[] ndsc;
	}
	if (ndscsum) {
		for (int m = 0; m < M; m++) {
			if (ndscsum[m]) {
				delete[] ndscsum[m];
			}
		}
	}
    if (theta) {
		for (int m = 0; m < M; m++) {
			if (theta[m]) {
				delete[] theta[m];
			}
		}
		delete[] theta;
    }

	if (aTheta) {
		for (int m = 0; m < M; m++) {
			if (aTheta[m]) {
				for (int s = 0; s < Sd[m]; s++) {
					if (aTheta[m][s]) {
						delete[] aTheta[m][s];
					}
				}
				delete[] aTheta[m];
			}
		}
		delete[] aTheta;
	}
    
    if (phi) {
		for (int k = 0; k < K; k++) {
			if (phi[k]) {
				delete[] phi[k];
			}
		}
		delete[] phi;
    }

    // only for inference
	if (newSd) {
		delete[] newSd;
	}

    if (newz) {
	for (int m = 0; m < newM; m++) {
	    if (newz[m]) {
		delete newz[m];
	    }
	}
    }
    
    if (newnw) {
	for (int w = 0; w < newV; w++) {
	    if (newnw[w]) {
		delete newnw[w];
	    }
	}
    }

    if (newnd) {
	for (int m = 0; m < newM; m++) {
	    if (newnd[m]) {
		delete newnd[m];
	    }
	}
    } 
	if (newnds) {
		for (int m = 0; m < newM; m++) {
			if (newnds[m]) {
				for (int s = 0; s < newSd[m]; s++) {
					if (newnds[m][s]) {
						delete[] newnds[m][s];
					}
				}
				delete[] newnds[m];
			}
		}
		delete[] newnds;
	}
	if (newndssum) {
		for (int m = 0; m < newM; m++) {
			if (newndssum[m]) {
				delete[] newndssum[m];
			}
		}
		delete[] newndssum;
	}
	if (newndsc) {
		for (int m = 0; m < newM; m++) {
			if (newndsc[m]) {
				for (int s = 0; s = newSd[m]; s++) {
					if (newndsc[m][s]) {
						delete[] newndsc[m][s];
					}
				}
				delete[] newndsc[m];
			}
		}
		delete[] newndsc;
	}
	if (newndscsum) {
		for (int m = 0; m < newM; m++) {
			if (newndscsum[m]) {
				delete[] newndscsum[m];
			}
		}
		delete[] newndscsum;
	}
    
    if (newnwsum) {
	delete newnwsum;
    }   
    
    if (newndsum) {
	delete newndsum;
    }
    
    if (newtheta) {
	for (int m = 0; m < newM; m++) {
	    if (newtheta[m]) {
		delete newtheta[m];
	    }
	}
    }
	if (newAtheta) {
		for (int m = 0; m < newM; m++) {
			if (newAtheta[m]) {
				for (int s = 0; s < newSd[m]; s++) {
					if (newAtheta[m][s]) {
						delete[] newAtheta[m][s];
					}
				}
				delete[] newAtheta[m];
			}
		}
		delete[] newAtheta;
	}
    
    if (newphi) {
	for (int k = 0; k < K; k++) {
	    if (newphi[k]) {
		delete newphi[k];
	    }
	}
    }
}

void model::set_default_values() {
    wordmapfile = "wordmap.txt";
    trainlogfile = "trainlog.txt";
    tassign_suffix = ".tassign";
    theta_suffix = ".theta";
    phi_suffix = ".phi";
    others_suffix = ".others";
    twords_suffix = ".twords";
    
    dir = "./";
    dfile = "trndocs.dat";
    model_name = "model-final";    
    model_status = MODEL_STATUS_UNKNOWN;
    
    ptrndata = NULL;



    pnewdata = NULL;
    
    M = 0;
    V = 0;
    K = 100;
	C = 4;
    alpha = 50.0 / K;
    beta = 0.1;
    niters = 2000;
    liter = 0;
    savestep = 200;    
    twords = 0;
    withrawstrs = 0;
    
	Sd = NULL;
    p1 = NULL;
	p2 = NULL;
    z = NULL;
    nw = NULL;
    nd = NULL;
	nds = NULL;
	ndsc = NULL;
	ndssum = NULL;
	ndscsum = NULL;
    nwsum = NULL;
    ndsum = NULL;
    theta = NULL;
    phi = NULL;
    
	newSd = NULL;
    newM = 0;
    newV = 0;
	newC = 0;
    newz = NULL;
    newnw = NULL;
    newnd = NULL;
	newnds = NULL;
	newndssum = NULL;
	newndsc = NULL;
	newndscsum = NULL;
    newnwsum = NULL;
    newndsum = NULL;
    newtheta = NULL;
    newphi = NULL;
}

int model::parse_args(int argc, char ** argv) {
    return utils::parse_args(argc, argv, this);
}

int model::init(int argc, char ** argv) {
    // call parse_args
    if (parse_args(argc, argv)) {
	return 1;
    }
    
    if (model_status == MODEL_STATUS_EST) {
	// estimating the model from scratch
		if (init_est()) {
			return 1;
		}
	
    } else if (model_status == MODEL_STATUS_ESTC) {
	// estimating the model from a previously estimated one
	if (init_estc()) {
	    return 1;
	}
	
    } else if (model_status == MODEL_STATUS_INF) {
	// do inference
	if (init_inf()) {
	    return 1;
	}
    }
    
    return 0;
}

int model::load_model(string model_name) {
    int i, j;
    
    string filename = dir + model_name + tassign_suffix;
    FILE * fin = fopen(filename.c_str(), "r");
    if (!fin) {
	printf("Cannot open file %d to load model!\n", filename.c_str());
	return 1;
    }
    
    char buff[BUFF_SIZE_LONG];
    string line;

    // allocate memory for z and ptrndata
    z = new int**[M];
    ptrndata = new dataset(M);
    ptrndata->V = V;

    for (i = 0; i < M; i++) {
		char * pointer = fgets(buff, BUFF_SIZE_LONG, fin);
		if (!pointer) {
			printf("Invalid word-topic assignment file, check the number of docs!\n");
			return 1;
		}
	
		line = buff;
		strtokenizer strtok(line, " \t\r\n");
		int length = strtok.count_tokens();
	
		vector<int> words;
		vector<int> topics;
		for (j = 0; j < length; j++) {
			string token = strtok.token(j);
    
			strtokenizer tok(token, ":");
			if (tok.count_tokens() != 2) {
			printf("Invalid word-topic assignment line!\n");
			return 1;
			}
	    
			words.push_back(atoi(tok.token(0).c_str()));
			topics.push_back(atoi(tok.token(1).c_str()));
		}
	
		// allocate and add new document to the corpus
		//todo
		document * pdoc = new document(words.size());
		ptrndata->add_doc(pdoc, i);
	
		// assign values for z
		z[i] = new int*[ptrndata->docs[i]->dsLength];
		for (j = 0; j < ptrndata->docs[i]->dsLength; j++) {
			for (int n = 0; n < ptrndata->docs[i]->sLength[j]; n++) {
				z[i][j][n] = topics[j];
			}
		}
    }   
    
    fclose(fin);
    
    return 0;
}

int model::save_model(string model_name) {
    if (save_model_tassign(dir + model_name + tassign_suffix)) {
	return 1;
    }
    
    if (save_model_others(dir + model_name + others_suffix)) {
	return 1;
    }
    
    if (save_model_theta(dir + model_name + theta_suffix)) {
	return 1;
    }
    
    if (save_model_phi(dir + model_name + phi_suffix)) {
	return 1;
    }
    
    if (twords > 0) {
	if (save_model_twords(dir + model_name + twords_suffix)) {
	    return 1;
	}
    }
    
    return 0;
}

int model::save_model_tassign(string filename) {
    int i, j;
    
    FILE * fout = fopen(filename.c_str(), "w");
    if (!fout) {
	printf("Cannot open file %s to save!\n", filename.c_str());
	return 1;
    }

    // wirte docs with topic assignments for words
    for (i = 0; i < ptrndata->M; i++) {    
	for (j = 0; j < ptrndata->docs[i]->length; j++) {
		//todo
	   // fprintf(fout, "%d:%d ", ptrndata->docs[i]->words[j], z[i][j]);
	}
	fprintf(fout, "\n");
    }

    fclose(fout);
    
    return 0;
}

int model::save_model_theta(string filename) {
    FILE * fout = fopen(filename.c_str(), "w");
    if (!fout) {
	printf("Cannot open file %s to save!\n", filename.c_str());
	return 1;
    }
    
    for (int i = 0; i < M; i++) {
	for (int j = 0; j < K; j++) {
	    fprintf(fout, "%f ", theta[i][j]);
	}
	fprintf(fout, "\n");
    }
    
    fclose(fout);
    
    return 0;
}

int model::save_model_phi(string filename) {
    FILE * fout = fopen(filename.c_str(), "w");
    if (!fout) {
	printf("Cannot open file %s to save!\n", filename.c_str());
	return 1;
    }
    
    for (int i = 0; i < K; i++) {
	for (int j = 0; j < V; j++) {
	    fprintf(fout, "%f ", phi[i][j]);
	}
	fprintf(fout, "\n");
    }
    
    fclose(fout);    
    
    return 0;
}

int model::save_model_others(string filename) {
    FILE * fout = fopen(filename.c_str(), "w");
    if (!fout) {
	printf("Cannot open file %s to save!\n", filename.c_str());
	return 1;
    }

    fprintf(fout, "alpha=%f\n", alpha);
    fprintf(fout, "beta=%f\n", beta);
    fprintf(fout, "ntopics=%d\n", K);
    fprintf(fout, "ndocs=%d\n", M);
    fprintf(fout, "nwords=%d\n", V);
    fprintf(fout, "liter=%d\n", liter);
    
    fclose(fout);    
    
    return 0;
}

int model::save_model_twords(string filename) {
    FILE * fout = fopen(filename.c_str(), "w");
    if (!fout) {
	printf("Cannot open file %s to save!\n", filename.c_str());
	return 1;
    }
    
    if (twords > V) {
	twords = V;
    }
    mapid2word::iterator it;
    
    for (int k = 0; k < K; k++) {
	vector<pair<int, double> > words_probs;
	pair<int, double> word_prob;
	for (int w = 0; w < V; w++) {
	    word_prob.first = w;
	    word_prob.second = phi[k][w];
	    words_probs.push_back(word_prob);
	}
    
        // quick sort to sort word-topic probability
	utils::quicksort(words_probs, 0, words_probs.size() - 1);
	
	fprintf(fout, "Topic %dth:\n", k);
	for (int i = 0; i < twords; i++) {
	    it = id2word.find(words_probs[i].first);
	    if (it != id2word.end()) {
		fprintf(fout, "\t%s   %f\n", (it->second).c_str(), words_probs[i].second);
	    }
	}
    }
    
    fclose(fout);    
    
    return 0;    
}

int model::save_inf_model(string model_name) {
    if (save_inf_model_tassign(dir + model_name + tassign_suffix)) {
	return 1;
    }
    
    if (save_inf_model_others(dir + model_name + others_suffix)) {
	return 1;
    }
    
    if (save_inf_model_newtheta(dir + model_name + theta_suffix)) {
	return 1;
    }
    
    if (save_inf_model_newphi(dir + model_name + phi_suffix)) {
	return 1;
    }

    if (twords > 0) {
	if (save_inf_model_twords(dir + model_name + twords_suffix)) {
	    return 1;
	}
    }
    
    return 0;
}

int model::save_inf_model_tassign(string filename) {
    int i, j;
    
    FILE * fout = fopen(filename.c_str(), "w");
    if (!fout) {
	printf("Cannot open file %s to save!\n", filename.c_str());
	return 1;
    }

    // wirte docs with topic assignments for words
    for (i = 0; i < pnewdata->M; i++) {    
	for (j = 0; j < pnewdata->docs[i]->length; j++) {
	//todo
	 //   fprintf(fout, "%d:%d ", pnewdata->docs[i]->words[j], newz[i][j]);
	}
	fprintf(fout, "\n");
    }

    fclose(fout);
    
    return 0;
}

int model::save_inf_model_newtheta(string filename) {
    int i, j;

    FILE * fout = fopen(filename.c_str(), "w");
    if (!fout) {
	printf("Cannot open file %s to save!\n", filename.c_str());
	return 1;
    }
    
    for (i = 0; i < newM; i++) {
	for (j = 0; j < K; j++) {
	    fprintf(fout, "%f ", newtheta[i][j]);
	}
	fprintf(fout, "\n");
    }
    
    fclose(fout);
    
    return 0;
}

int model::save_inf_model_newphi(string filename) {
    FILE * fout = fopen(filename.c_str(), "w");
    if (!fout) {
	printf("Cannot open file %s to save!\n", filename.c_str());
	return 1;
    }
    
    for (int i = 0; i < K; i++) {
	for (int j = 0; j < newV; j++) {
	    fprintf(fout, "%f ", newphi[i][j]);
	}
	fprintf(fout, "\n");
    }
    
    fclose(fout);    
    
    return 0;
}

int model::save_inf_model_others(string filename) {
    FILE * fout = fopen(filename.c_str(), "w");
    if (!fout) {
	printf("Cannot open file %s to save!\n", filename.c_str());
	return 1;
    }

    fprintf(fout, "alpha=%f\n", alpha);
    fprintf(fout, "beta=%f\n", beta);
    fprintf(fout, "ntopics=%d\n", K);
    fprintf(fout, "ndocs=%d\n", newM);
    fprintf(fout, "nwords=%d\n", newV);
    fprintf(fout, "liter=%d\n", inf_liter);
    
    fclose(fout);    
    
    return 0;
}

int model::save_inf_model_twords(string filename) {
    FILE * fout = fopen(filename.c_str(), "w");
    if (!fout) {
	printf("Cannot open file %s to save!\n", filename.c_str());
	return 1;
    }
    
    if (twords > newV) {
	twords = newV;
    }
    mapid2word::iterator it;
    map<int, int>::iterator _it;
    
    for (int k = 0; k < K; k++) {
	vector<pair<int, double> > words_probs;
	pair<int, double> word_prob;
	for (int w = 0; w < newV; w++) {
	    word_prob.first = w;
	    word_prob.second = newphi[k][w];
	    words_probs.push_back(word_prob);
	}
    
        // quick sort to sort word-topic probability
	utils::quicksort(words_probs, 0, words_probs.size() - 1);
	
	fprintf(fout, "Topic %dth:\n", k);
	for (int i = 0; i < twords; i++) {
	    _it = pnewdata->_id2id.find(words_probs[i].first);
	    if (_it == pnewdata->_id2id.end()) {
		continue;
	    }
	    it = id2word.find(_it->second);
	    if (it != id2word.end()) {
		fprintf(fout, "\t%s   %f\n", (it->second).c_str(), words_probs[i].second);
	    }
	}
    }
    
    fclose(fout);    
    
    return 0;    
}


int model::init_est() {
    int m,s, n, w, k;

    p1 = new double[K];
	p2 = new double[C];

    // + read training data
    ptrndata = new dataset;
    if (ptrndata->read_trndata(dir + dfile, dir + wordmapfile)) {
        printf("Fail to read training data!\n");
        return 1;
    }
		
    // + allocate memory and assign values for variables
    M = ptrndata->M;
    V = ptrndata->V;
    // K: from command line or default value
    // alpha, beta: from command line or default values
    // niters, savestep: from command line or default values

    nw = new int*[V];
    for (w = 0; w < V; w++) {
        nw[w] = new int[K];
        for (k = 0; k < K; k++) {
    	    nw[w][k] = 0;
        }
    }
	
    nd = new int*[M];
    for (m = 0; m < M; m++) {
        nd[m] = new int[K];
        for (k = 0; k < K; k++) {
    	    nd[m][k] = 0;
        }
    }
	
    nwsum = new int[K];
    for (k = 0; k < K; k++) {
	nwsum[k] = 0;
    }
    
    ndsum = new int[M];
    for (m = 0; m < M; m++) {
	ndsum[m] = 0;
    }
	//初始化每篇文章中句子数量
	Sd = new int[M];
	for (m = 0; m < M; m++) {
		Sd[m] = ptrndata->docs[m]->dsLength;
	}
	//初始化文章m,句子s中分配到主题k中的单词数量
	nds = new int**[M];
	for (m = 0; m < M; m++) {
		nds[m] = new int*[Sd[m]];
		for (s = 0; s < Sd[m]; s++) {
			nds[m][s] = new int[K];
			for (int k = 0; k < K; k++) {
				nds[m][s][k] = 0;
			}
		}
	}
	//初始化文章m,句子s的单词个数
	ndssum = new int*[M];
	for (m = 0; m < M; m++) {
		ndssum[m] = new int[Sd[m]];
		for (s = 0; s < Sd[m]; s++) {
			ndssum[m][s] = 0;
		}
	}
	//初始化文章m，句子s的Attention
	ndsc = new int**[M];
	for (m = 0; m < M; m++) {
		ndsc[m] = new int*[Sd[m]];
		for (s = 0; s < Sd[m]; s++) {
			ndsc[m][s] = new int[C];
			for (int c = 0; c < C; c++) {
				ndsc[m][s][c] = 0;
			}
		}
	}
	//initialize the attention count of a sentance s in document m;
	ndscsum = new int*[M];
	for (m = 0; m < M; n++) {
		ndscsum[m] = new int[Sd[m]];
		for (s = 0; s < Sd[m]; s++) {
			ndscsum[m][s] = 0;
		}
	}


    srand(time(0)); // initialize for random number generation
	//initialize the topic of each word in sentance s of document m
    z = new int**[M];
	at = new int**[M];
    for (m = 0; m < ptrndata->M; m++) {
		int* &_Sd = ptrndata->docs[m]->sLength;
		int sCount = ptrndata->docs[m]->dsLength;
		z[m] = new int*[sCount];
		z[m] = new int*[sCount];
		for (s = 0; s < sCount; ) {
			z[m][s] = new int[_Sd[s]];
			z[m][s] = new int[_Sd[s]];
			for (n = 0; n < _Sd[s]; n++) {
				int topic = (int)(((double)rand() / RAND_MAX) * K);
				z[m][s][n] = topic;
				//word n assigned to topic , plus 1 p(w|z)
				nw[ptrndata->docs[m]->sentances[s][n]][topic] += 1;
				nwsum[topic] += 1;
				//p(z|θ)
				nd[m][topic] += 1;
				ndsum[m] = +1;
				//p(z|θsi)
				nds[m][s][topic] += 1;
				ndssum[m][s] += 1;
				//随机分配attention
				int _at = (int)((((double)rand() / RAND_MAX) * C));
				if (n < C-1) {
					_at = n;
				}
				at[m][s][n] = _at;
				ndsc[m][s][_at] = 1;
				ndscsum[m][s] += 1;
			}
		}
			    
    }


    
    aTheta = new double**[M];
    for (m = 0; m < M; m++) {
        aTheta[m] = new double*[ptrndata->docs[m]->dsLength];
		for (s = 0; s < ptrndata->docs[m]->dsLength; s++) {
			aTheta[m][s] = new double[K];
		}
    }
	
    phi = new double*[K];
    for (k = 0; k < K; k++) {
        phi[k] = new double[V];
    }    
    
    return 0;
}

int model::init_estc() {
    // estimating the model from a previously estimated one
    int m,s, n, w, k;
	if (NULL == p1) {
		p1 = new double[K];
	}
	if(NULL==p2) {
		p2 = new double[C];
	}	

    // load moel, i.e., read z and ptrndata
    if (load_model(model_name)) {
	printf("Fail to load word-topic assignmetn file of the model!\n");
	return 1;
    }

	nw = new int*[V];
	for (w = 0; w < V; w++) {
		nw[w] = new int[K];
		for (k = 0; k < K; k++) {
			nw[w][k] = 0;
		}
	}

	nd = new int*[M];
	for (m = 0; m < M; m++) {
		nd[m] = new int[K];
		for (k = 0; k < K; k++) {
			nd[m][k] = 0;
		}
	}

	nwsum = new int[K];
	for (k = 0; k < K; k++) {
		nwsum[k] = 0;
	}

	ndsum = new int[M];
	for (m = 0; m < M; m++) {
		ndsum[m] = 0;
	}
	//初始化每篇文章中句子数量
	Sd = new int[M];
	for (m = 0; m < M; m++) {
		Sd[m] = ptrndata->docs[m]->dsLength;
	}
	//初始化文章m,句子s中分配到主题k中的单词数量
	nds = new int**[M];
	for (m = 0; m < M; m++) {
		nds[m] = new int*[Sd[m]];
		for (s = 0; s < Sd[m]; s++) {
			nds[m][s] = new int[K];
			for (int k = 0; k < K; k++) {
				nds[m][s][k] = 0;
			}
		}
	}
	//初始化文章m,句子s的单词个数
	ndssum = new int*[M];
	for (m = 0; m < M; m++) {
		ndssum[m] = new int[Sd[m]];
		for (s = 0; s < Sd[m]; s++) {
			ndssum[m][s] = 0;
		}
	}
	//初始化文章m，句子s的Attention
	ndsc = new int**[M];
	for (m = 0; m < M; m++) {
		ndsc[m] = new int*[Sd[m]];
		for (s = 0; s < Sd[m]; s++) {
			ndsc[m][s] = new int[C];
			for (int c = 0; c < C; c++) {
				ndsc[m][s][c] = 0;
			}
		}
	}
	//initialize the attention count of a sentance s in document m;
	ndscsum = new int*[M];
	for (m = 0; m < M; n++) {
		ndscsum[m] = new int[Sd[m]];
		for (s = 0; s < Sd[m]; s++) {
			ndscsum[m][s] = 0;
		}
	}


	z = new int**[M];
	for (m = 0; m < ptrndata->M; m++) {
		int* &_Sd = ptrndata->docs[m]->sLength;
		int sCount = ptrndata->docs[m]->dsLength;
		z[m] = new int*[sCount];
		for (s = 0; s < sCount; ) {
			z[m][s] = new int[_Sd[s]];
			for (n = 0; n < _Sd[s]; n++) {
				int word = ptrndata->docs[m]->sentances[s][n];
				int topic = z[m][s][n];
				//word n assigned to topic , plus 1 p(w|z)
				nw[word][topic] += 1;
				nwsum[topic] += 1;
				//p(z|θ)
				nd[m][topic] += 1;
				ndsum[m] = +1;
				//p(z|θsi)
				nds[m][s][topic] += 1;
				ndssum[m][s] += 1;
			}
		}

	}

	aTheta = new double**[M];
	for (m = 0; m < M; m++) {
		aTheta[m] = new double*[ptrndata->docs[m]->dsLength];
		for (s = 0; s < ptrndata->docs[m]->dsLength; s++) {
			aTheta[m][s] = new double[K];
		}
	}

	phi = new double*[K];
	for (k = 0; k < K; k++) {
		phi[k] = new double[V];
	}

    return 0;        
}

void model::estimate() {
    if (twords > 0) {
	// print out top words per topic
	dataset::read_wordmap(dir + wordmapfile, &id2word);
    }

    printf("Sampling %d iterations!\n", niters);

    int last_iter = liter;
    for (liter = last_iter + 1; liter <= niters + last_iter; liter++) {
		printf("Iteration %d ...\n", liter);
	
		// for all z_i
		for (int m = 0; m < M; m++) {
			for (int s = 0; s < ptrndata->docs[m]->dsLength; s++) {
				for (int n = 0; n < ptrndata->docs[m]->sLength[s]; n++) {
					int attention = samplingAttention(m, s, n);
					at[m][s][n] = attention;
					int topic = samplingTopic(m, s, n);
					z[m][s][n] = topic;
				}
			}
			
		}
	
		if (savestep > 0) {
			if (liter % savestep == 0) {
			// saving the model
			printf("Saving the model at iteration %d ...\n", liter);
			compute_theta();
			compute_aTheta();
			compute_phi();
			save_model(utils::generate_model_name(liter));
			}
		}
    }
    
    printf("Gibbs sampling completed!\n");
    printf("Saving the final model!\n");
    compute_theta();
	compute_aTheta();
    compute_phi();
    liter--;
    save_model(utils::generate_model_name(-1));
}


int model::samplingAttention(int m, int s, int n){
	int atC = at[m][s][n];
	int w = ptrndata->docs[m]->sentances[s][n];

	ndsc[m][s][atC] -= 1;
	ndscsum[m][s] -= 1;
	//choose a topic distribution with probability \epsilon_i


	for (atC = 0; atC < C; atC++) {
		p2[atC] = 0;
		if(atC==0)
		for (int k = 0; k < K; k++) {
			p2[atC] += (nw[w][k] + beta) / (nwsum[k] + V*beta)*
				(nds[m][s - atC][k] + alpha) / (ndssum[m][s - atC] + K*alpha)*
				(ndsc[m][s][atC] + pi) / (ndscsum[m][s] + C*pi);
		}
	}
	for (int c = 1; c < C; c++) {
		p2[c] += p2[c - 1];
	}
	double sel = ((double)rand() / RAND_MAX) / p2[C - 1];
	for (atC = 0; atC < C; atC++) {
		if (sel < p2[atC]) {
			break;
		}
	}
	ndsc[m][s][atC] += 1;
	ndsc[m][s][atC] += 1;
}

int model::samplingTopic(int m, int s, int n) {
    // remove z_i from the count variables
    int topic = z[m][s][n];
	int atC = at[m][s][n];
    int w = ptrndata->docs[m]->sentances[s][n];
    nw[w][topic] -= 1;
    nd[m][topic] -= 1;
	nds[m][s][topic] -= 1;
	ndssum[m][s] -= 1;
    nwsum[topic] -= 1;
    ndsum[m] -= 1;

    double Vbeta = V * beta;
    double Kalpha = K * alpha;    
    // do multinomial sampling via cumulative method
	for (int k = 0; k < K; k++) {
		if (atC = 0||s-atC<0) {
			p1[k] = (nw[w][k] + beta) / (nwsum[k] + Vbeta) *
				(nd[m][k] + alpha) / (ndsum[m] + Kalpha);
		}
		else {
			p1[k] = (nw[w][k] + beta) / (nwsum[k] + Vbeta) *
				(nds[m][s-atC][k] + alpha) / (ndssum[m][s-atC] + Kalpha);
		}
	}
    
    // cumulate multinomial parameters
    for (int k = 1; k < K; k++) {
		p1[k] += p1[k - 1];
    }
    // scaled sample because of unnormalized p[]
    double u = ((double)rand() / RAND_MAX) * p1[K - 1];
    
    for (topic = 0; topic < K; topic++) {
		if (p1[topic] > u) {
			break;
		}
    }
    
    // add newly estimated z_i to count variables
    nw[w][topic] += 1;
    nd[m][topic] += 1;
    nwsum[topic] += 1;
    ndsum[m] += 1;
	nds[m][s][topic] += 1;
	ndssum[m][s] += 1;
    
    return topic;
}

void model::compute_theta() {
    for (int m = 0; m < M; m++) {
	for (int k = 0; k < K; k++) {
	    theta[m][k] = (nd[m][k] + alpha) / (ndsum[m] + K * alpha);
	}
    }
}

void model::compute_aTheta() {

}

void model::compute_phi() {
    for (int k = 0; k < K; k++) {
	for (int w = 0; w < V; w++) {
	    phi[k][w] = (nw[w][k] + beta) / (nwsum[k] + V * beta);
	}
    }
}

int model::init_inf() {
	/*
    // estimating the model from a previously estimated one
    int m, n, w, k;
	if (NULL == p1) {
		p1 = new double[K];
	}
	if (NULL == p2) {
		p2 = new double[C];
	}
    

    // load moel, i.e., read z and ptrndata
    if (load_model(model_name)) {
	printf("Fail to load word-topic assignmetn file of the model!\n");
	return 1;
    }

    nw = new int*[V];
    for (w = 0; w < V; w++) {
        nw[w] = new int[K];
        for (k = 0; k < K; k++) {
    	    nw[w][k] = 0;
        }
    }
	
    nd = new int*[M];
    for (m = 0; m < M; m++) {
        nd[m] = new int[K];
        for (k = 0; k < K; k++) {
    	    nd[m][k] = 0;
        }
    }
	
    nwsum = new int[K];
    for (k = 0; k < K; k++) {
	nwsum[k] = 0;
    }
    
    ndsum = new int[M];
    for (m = 0; m < M; m++) {
		ndsum[m] = 0;
    }
	//m is the document order-num
    for (m = 0; m < ptrndata->M; m++) {
		//N is the length of m-th document
		int N = ptrndata->docs[m]->length;

		// assign values for nw, nd, nwsum, and ndsum	
        for (n = 0; n < N; n++) {
    	    int w = ptrndata->docs[m]->words[n];
			//z 是如何获取的，即文档中对应的单词所属的主题
    	    int topic = z[m][n];
    	    
    	    // number of instances of word i assigned to topic j
			//数据集中每个单词对应主题次数的统计
    	    nw[w][topic] += 1;
    	    // number of words in document i assigned to topic j
			//数据集中每个文档主题出现次数的统计
    	    nd[m][topic] += 1;

    	    // total number of words assigned to topic j
			// 数据集中每个主题的出现次数
    	    nwsum[topic] += 1;
        } 
        // total number of words in document i
        ndsum[m] = N;      
    }
    
    // read new data for inference
    pnewdata = new dataset;
    if (withrawstrs) {
		if (pnewdata->read_newdata_withrawstrs(dir + dfile, dir + wordmapfile)) {
    			printf("Fail to read new data!\n");
    			return 1;
		}    
    } else {
		if (pnewdata->read_newdata(dir + dfile, dir + wordmapfile)) {
    			printf("Fail to read new data!\n");
    			return 1;
		}    
    }
    
    newM = pnewdata->M;
    newV = pnewdata->V;
    
    newnw = new int*[newV];
    for (w = 0; w < newV; w++) {
        newnw[w] = new int[K];
        for (k = 0; k < K; k++) {
    	    newnw[w][k] = 0;
        }
    }
	
    newnd = new int*[newM];
    for (m = 0; m < newM; m++) {
        newnd[m] = new int[K];
        for (k = 0; k < K; k++) {
    	    newnd[m][k] = 0;
        }
    }
	
    newnwsum = new int[K];
    for (k = 0; k < K; k++) {
		newnwsum[k] = 0;
    }
    
    newndsum = new int[newM];
    for (m = 0; m < newM; m++) {
	newndsum[m] = 0;
    }

    srand(time(0)); // initialize for random number generation
    newz = new int*[newM];
    for (m = 0; m < pnewdata->M; m++) {
		int N = pnewdata->docs[m]->length;
		newz[m] = new int[N];

		// assign values for nw, nd, nwsum, and ndsum	
        for (n = 0; n < N; n++) {
    	    int w = pnewdata->docs[m]->words[n];
    	    int _w = pnewdata->_docs[m]->words[n];
    	    int topic = (int)(((double)rand() / RAND_MAX) * K);
    	    newz[m][n] = topic;
    	    
    	    // number of instances of word i assigned to topic j
    	    newnw[_w][topic] += 1;
    	    // number of words in document i assigned to topic j
    	    newnd[m][topic] += 1;
    	    // total number of words assigned to topic j
    	    newnwsum[topic] += 1;
        } 
        // total number of words in document i
        newndsum[m] = N;      
    }    
    
    newtheta = new double*[newM];
    for (m = 0; m < newM; m++) {
        newtheta[m] = new double[K];
    }
	
    newphi = new double*[K];
    for (k = 0; k < K; k++) {
        newphi[k] = new double[newV];
    }    
    */
    return 0;        
}

void model::inference() {
	/*
    if (twords > 0) {
	// print out top words per topic
	dataset::read_wordmap(dir + wordmapfile, &id2word);
    }

    printf("Sampling %d iterations for inference!\n", niters);
    
    for (inf_liter = 1; inf_liter <= niters; inf_liter++) {
		printf("Iteration %d ...\n", inf_liter);
	
		// for all newz_i
		for (int m = 0; m < newM; m++) {
			for (int n = 0; n < pnewdata->docs[m]->length; n++) {
			// (newz_i = newz[m][n])
			// sample from p(z_i|z_-i, w)
			int topic = inf_sampling(m, n);
			newz[m][n] = topic;
			}
		}
    }
    
    printf("Gibbs sampling for inference completed!\n");
    printf("Saving the inference outputs!\n");
    compute_newtheta();
    compute_newphi();
    inf_liter--;
    save_inf_model(dfile);
	*/
}

int model::inf_sampling(int m, int n) {
	/*
    // remove z_i from the count variables
    int topic = newz[m][n];
    int w = pnewdata->docs[m]->words[n];
    int _w = pnewdata->_docs[m]->words[n];
    newnw[_w][topic] -= 1;
    newnd[m][topic] -= 1;
    newnwsum[topic] -= 1;
    newndsum[m] -= 1;
    
    double Vbeta = V * beta;
    double Kalpha = K * alpha;
    // do multinomial sampling via cumulative method
    for (int k = 0; k < K; k++) {
		p[k] = (nw[w][k] + newnw[_w][k] + beta) / (nwsum[k] + newnwsum[k] + Vbeta) *
				(newnd[m][k] + alpha) / (newndsum[m] + Kalpha);
    }
    // cumulate multinomial parameters
    for (int k = 1; k < K; k++) {
		p[k] += p[k - 1];
    }
    // scaled sample because of unnormalized p[]
    double u = ((double)rand() / RAND_MAX) * p[K - 1];
    
    for (topic = 0; topic < K; topic++) {
		if (p[topic] > u) {
			break;
		}
    }
    
    // add newly estimated z_i to count variables
    newnw[_w][topic] += 1;
    newnd[m][topic] += 1;
    newnwsum[topic] += 1;
    newndsum[m] += 1;    
    return topic;
	*/
}

void model::compute_newtheta() {
    for (int m = 0; m < newM; m++) {
	for (int k = 0; k < K; k++) {
	    newtheta[m][k] = (newnd[m][k] + alpha) / (newndsum[m] + K * alpha);
	}
    }
}

void model::compute_newphi() {
    map<int, int>::iterator it;
    for (int k = 0; k < K; k++) {
	for (int w = 0; w < newV; w++) {
	    it = pnewdata->_id2id.find(w);
	    if (it != pnewdata->_id2id.end()) {
		newphi[k][w] = (nw[it->second][k] + newnw[w][k] + beta) / (nwsum[k] + newnwsum[k] + V * beta);
	    }
	}
    }
}

