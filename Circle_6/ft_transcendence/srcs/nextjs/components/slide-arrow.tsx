'use client'

import { ChevronDownIcon, ChevronUpIcon } from "@heroicons/react/24/outline";

interface SlideArrowProps {
    targetId: string;
    direction?: 'up' | 'down';
}

export default function SlideArrow({ targetId, direction = 'down' }: SlideArrowProps) {
    const scrollToSlide = () => {
        const element = document.getElementById(targetId);
        if (element) {
            element.scrollIntoView({ behavior: 'smooth' });
        }
    };

    return (
        <button
            onClick={scrollToSlide}
            className="absolute bottom-8 left-1/2 -translate-x-1/2 text-surface-900/90 hover:text-surface-900/85 animate-bounce cursor-pointer transition-all"
            aria-label={direction === 'up' ? 'Slide précédente' : 'Slide suivante'}
        >
            {direction === 'up'
                ? <ChevronUpIcon className="w-10 h-10" />
                : <ChevronDownIcon className="w-10 h-10" />}
        </button>
    );
}