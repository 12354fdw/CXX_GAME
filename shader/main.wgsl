requires immediate_address_space;

struct ImmediateData {
    mvp: mat4x4f,
}

var<immediate> pushConstants: ImmediateData;

struct VertexInput {
	@location(0) position: vec3f,
	@location(1) color: vec3f,
	@location(2) normal: vec3f,
}

struct VertexOutput {
	@builtin(position) position: vec4f,
	@location(0) color: vec3f,
	@location(1) normal: vec3f,
}

@vertex
fn vs_main(in: VertexInput) -> VertexOutput {
	var out: VertexOutput;

	out.position = pushConstants.mvp * vec4<f32>(in.position, 1.0);

	out.normal = in.normal;
	out.color = in.color;

	return out;
}

@fragment
fn fs_main(in: VertexOutput) -> @location(0) vec4f {
	let N = normalize(in.normal);
	let L = normalize(vec3f(0.5, 1.0, 0.3));
	
	let diffuseFactor = max(dot(N, L), 0.0);

	let ambient = 0.2;
    let totalLight = ambient + (diffuseFactor * 0.8);

	return vec4f(in.color * totalLight, 1.0);
}
