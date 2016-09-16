// All calculative functions

wheelLoad* calculateWheelLoad(loggedData* data,carData* cData)
{
	wheelLoad* w = (wheelLoad* )malloc(sizeof(struct WheelLoad));
	float ef = (cData->track.front)/1000;						// m
	float er = (cData->track.rear)/1000;						// m
	float mv = cData->carWeight + cData->driverWeight; 			// kgs
	float l = (cData->wheelbase)/1000;							// m
	float h = (cData->cg.z)/1000;								// m
	float lf = (cData->cg.x)/1000;								// m
	float lr = l - lf;											// m
	float ax = data->gForce.longitudnal;						// m/sec^2
	float ay = data->gForce.lateral;							// m/sec^2
	w->FL = mv*((lr-h*ax)/l)*(0.5-((h*ay)/(ef)));
	w->FR = mv*((lr-h*ax)/l)*(0.5+((h*ay)/(ef)));
	w->RL = mv*((lf+h*ax)/l)*(0.5-((h*ay)/(ef)));
	w->RR = mv*((lf+h*ax)/l)*(0.5+((h*ay)/(ef)));
	return w;
}

outputTorque* preventSlip(loggedData* data)
{
	outputTorque* output = (outputTorque*)malloc(sizeof(struct OutputTorque));
	return output;
}
