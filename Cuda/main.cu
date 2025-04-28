int main(){
	
	int num_pixels = nx*ny;
	size_t fb_size = 3 * num_pixels * sizeof(float); //allocate rgb floats for each pixel

	float *fb; 
	checkCudaErrors(cudaMallocManaged((void**)&fb), fb_size));

	int tx = 8; 
	int ty = 8; // we use blocks of 8*8 threads **multiple of 32 so can fit in warps



	dim3 blocks(nx/tx+1, ny/ty+1);
	dim3 threads(tx,ty);






}


__global__ void render(float *fb, int max_x, int max_y)
{
	int i = threadIdx.x + blockIdx.x * blockDim.x;
	int j = threadIdx.y + blockIdx.y * blockDim.y;

	if(())
}

