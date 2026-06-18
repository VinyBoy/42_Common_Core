'use client';

import { useState, useEffect, useRef } from 'react';

const KEYWORDS = [
  { article: 'de la', mot: 'Photographie' },
  { article: 'de la', mot: 'Peinture' },
  { article: 'de la', mot: 'Musique' },
  { article: 'de la', mot: 'Sculpture' },
  { article: "de l'", mot: 'Art Digital' },
  { article: 'du',    mot: 'Cinéma' },
  { article: 'de la', mot: 'Danse' },
  { article: "de l'", mot: 'Illustration' },
];

const INTERVAL_MS = 2500;

export default function RotatingKeyword() {
  const [index, setIndex] = useState(0);
  const [fade, setFade] = useState(true);
  const timeoutRef = useRef<ReturnType<typeof setTimeout> | null>(null);

  useEffect(() => {
    const prefersReducedMotion = window.matchMedia('(prefers-reduced-motion: reduce)').matches;
    if (prefersReducedMotion) return;

    const intervalId = setInterval(() => {
      setFade(false);
      timeoutRef.current = setTimeout(() => {
        setIndex((prev) => (prev + 1) % KEYWORDS.length);
        setFade(true);
      }, 300);
    }, INTERVAL_MS);

    return () => {
      clearInterval(intervalId);
      if (timeoutRef.current) clearTimeout(timeoutRef.current);
    };
  }, []);

  return (
    <span
      aria-live="polite"
      aria-atomic="true"
      className={`inline-block transition-opacity duration-300 ${
        fade ? 'opacity-100' : 'opacity-0'
      }`}
    >
      <span className="text-foreground/70">{KEYWORDS[index].article}{KEYWORDS[index].article.endsWith("'") ? '' : ' '}</span>
      <span className="text-accent-400">{KEYWORDS[index].mot}</span>
    </span>
  );
}
