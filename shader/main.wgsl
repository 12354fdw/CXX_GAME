requires immediate_address_space;

var<immediate> mvp: mat4x4f;

struct VertexInput {
	@location(0) position: vec3f,
	@location(1) color: vec3f,
}

struct VertexOutput {
	@builtin(position) position: vec4f,
	@location(0) color: vec3f,	
}

@vertex
fn vs_main(in: VertexInput) -> VertexOutput {
	let ratio = 640.0 / 480.0;

	var out: VertexOutput;

	out.position = mvp * vec4<f32>(in.position, 1.0);
	out.color = in.color;

	return out;
}

@fragment
fn fs_main(in: VertexOutput) -> @location(0) vec4f {
	return vec4f(in.color, 1.0);
}
