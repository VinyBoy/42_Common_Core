import client from "prom-client";

type MetricsState = {
	register : client.Registry;
	httpRequestTotal: client.Counter<"method" | "route" | "status_code">;
	httpRequestDurationSeconds: client.Histogram<"method" | "route" | "status_code">;
};

declare global
{
	var __metrics_state__: MetricsState | undefined;
}

function buildMetricsState(): MetricsState 
{
	const register = new client.Registry();

	register.setDefaultLabels({
		app: "transcendance-nextjs",
		env: process.env.NODE_ENV ?? "development",
	});

	client.collectDefaultMetrics({ register });

	const httpRequestTotal = new client.Counter<"method" | "route" | "status_code">({
		name: "http_requests_total",
		help: "Total number of HTTP requests",
		labelNames: ["method", "route", "status_code"],
		registers: [register],
	});

	const httpRequestDurationSeconds = new client.Histogram<"method" | "route" | "status_code">({
		name: "http_request_duration_seconds",
		help: "HTTP request duration in seconds",
		labelNames: ["method", "route", "status_code"],
		buckets: [0.005, 0.01, 0.025, 0.05, 0.1, 0.3, 1, 3],
		registers: [register],
	});

	return {
		register,
		httpRequestTotal,
		httpRequestDurationSeconds,
	};
}

const metricsState = globalThis.__metrics_state__ ?? buildMetricsState();

if (!globalThis.__metrics_state__) {
	globalThis.__metrics_state__ = metricsState;
}

export { metricsState };
