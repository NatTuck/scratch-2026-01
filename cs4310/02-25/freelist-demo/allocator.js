// Free List Memory Allocator Implementation

// Constants
const PAGE_SIZE = 4096; // 4KB pages
const HEADER_SIZE = 8; // Size of header in bytes (64-bit pointers/longs)
const MIN_BLOCK_SIZE = 16; // Minimum block size (header + next pointer)

// Global variables
let pages = []; // Array of memory pages
let freeList = null; // Head of free list
let nextPageId = 0; // Counter for page IDs
let nextBlockId = 0; // Counter for block IDs

// Block structure
class Block {
    constructor(size, isFree, pageId, offset) {
        this.id = nextBlockId++;
        this.size = size;
        this.isFree = isFree;
        this.pageId = pageId;
        this.offset = offset;
        this.next = null; // Next block in free list
        this.elementId = `block-${this.id}`; // DOM element ID
    }
    
    // Get the actual memory address of this block
    getAddress() {
        const page = pages[this.pageId];
        // Pages start at address 4096, then 8192, etc.
        const pageBaseAddress = (this.pageId + 1) * PAGE_SIZE;
        return pageBaseAddress + this.offset;
    }
}

// Page structure
class Page {
    constructor() {
        this.id = nextPageId++;
        this.blocks = []; // Blocks in this page
        this.elementId = `page-${this.id}`; // DOM element ID
        this.usedSpace = 0; // Bytes used in this page
    }
    
    // Get the base address of this page
    getBaseAddress() {
        return (this.id + 1) * PAGE_SIZE;
    }
}

// Initialize the allocator
function initAllocator() {
    // Reset globals
    pages = [];
    freeList = null;
    nextPageId = 0;
    nextBlockId = 0;
    
    // Start with empty state (no pages allocated initially)
    
    // Setup event listeners
    document.getElementById('malloc-btn').addEventListener('click', handleMalloc);
    document.getElementById('free-btn').addEventListener('click', handleFree);
    document.getElementById('realloc-btn').addEventListener('click', handleRealloc);
    document.getElementById('reset-btn').addEventListener('click', resetAllocator);
    
    // Render initial state
    renderMemory();
    updateStats();
    showFreeListInfo(); // Show initial free list info
}

// Allocate a new 4KB page
function allocateNewPage() {
    const page = new Page();
    pages.push(page);
    
    // Create one big free block for the entire page
    const blockSize = PAGE_SIZE - HEADER_SIZE;
    const block = new Block(blockSize, true, page.id, HEADER_SIZE);
    page.blocks.push(block);
    page.usedSpace = HEADER_SIZE;
    
    // Add to free list
    addToFreeList(block);
    
    return page;
}

// Add a block to the free list
function addToFreeList(block) {
    block.isFree = true;
    
    // Simple first-fit: add to beginning of list
    block.next = freeList;
    freeList = block;
}

// Remove a block from the free list
function removeFromFreeList(block) {
    if (freeList === block) {
        freeList = block.next;
        block.next = null;
        return;
    }
    
    let current = freeList;
    while (current && current.next !== block) {
        current = current.next;
    }
    
    if (current && current.next === block) {
        current.next = block.next;
        block.next = null;
    }
}

// Find a free block of at least the specified size
function findFreeBlock(size) {
    let current = freeList;
    while (current) {
        if (current.isFree && current.size >= size) {
            return current;
        }
        current = current.next;
    }
    return null;
}

// Split a block if it's large enough
function splitBlock(block, size) {
    // Only split if there's enough space for a new block
    const minSplitSize = size + MIN_BLOCK_SIZE;
    if (block.size >= minSplitSize) {
        // Remove the block from free list first
        removeFromFreeList(block);
        
        // Calculate size for new block
        const newSize = block.size - size - HEADER_SIZE;
        
        // Update current block
        block.size = size;
        block.isFree = false;
        
        // Create new free block
        const newBlock = new Block(newSize, true, block.pageId, block.offset + size + HEADER_SIZE);
        
        // Add new block to page
        const page = pages[block.pageId];
        const index = page.blocks.indexOf(block);
        page.blocks.splice(index + 1, 0, newBlock);
        
        // Add both blocks to free list (the new one, and potentially the original if it was supposed to stay)
        // But in this case, we want to return the allocated block and free the remainder
        addToFreeList(newBlock);
        
        return block;
    }
    
    // Just mark as allocated
    block.isFree = false;
    removeFromFreeList(block);
    return block;
}

// Coalesce adjacent free blocks
function coalesceBlocks() {
    for (const page of pages) {
        for (let i = 0; i < page.blocks.length - 1; i++) {
            const current = page.blocks[i];
            const next = page.blocks[i + 1];
            
            // Check if both blocks are free and adjacent
            if (current.isFree && next.isFree && 
                current.offset + current.size + HEADER_SIZE === next.offset) {
                
                // Merge blocks
                current.size += next.size + HEADER_SIZE;
                
                // Remove next block from free list
                removeFromFreeList(next);
                
                // Remove next block from page
                page.blocks.splice(i + 1, 1);
                
                // Also remove from DOM
                const element = document.getElementById(next.elementId);
                if (element) {
                    element.remove();
                }
                
                // Decrement i to recheck this position
                i--;
            }
        }
    }
}

// Malloc implementation
function malloc(size) {
    // Add header size
    size += HEADER_SIZE;
    
    // Ensure minimum block size
    size = Math.max(size, MIN_BLOCK_SIZE);
    
    // Check if size > 4KB (in real implementation, we'd use mmap)
    if (size > PAGE_SIZE) {
        showMessage(`Cannot allocate ${size} bytes - larger than page size`, 'error');
        return null;
    }
    
    // Search free list for suitable block
    let block = findFreeBlock(size);
    
    // If no suitable block, allocate new page
    if (!block) {
        allocateNewPage();
        block = findFreeBlock(size);
    }
    
    // If still no block, something went wrong
    if (!block) {
        showMessage('Failed to allocate memory', 'error');
        return null;
    }
    
    // Split block if necessary
    block = splitBlock(block, size);
    
    // Update page used space
    const page = pages[block.pageId];
    page.usedSpace += block.size + HEADER_SIZE;
    
    // Store size in header (simulated)
    // In real implementation, this would be stored in the actual memory
    
    renderMemory();
    updateStats();
    showFreeListInfo(); // Show free list info after each operation
    
    // Return pointer (the actual address)
    return block.getAddress().toString();
}

// Free implementation
function free(ptr) {
    if (!ptr) {
        showMessage('Invalid pointer', 'error');
        return;
    }
    
    const address = parseInt(ptr);
    if (isNaN(address)) {
        showMessage('Invalid pointer address', 'error');
        return;
    }
    
    // Find block by address
    let targetBlock = null;
    let targetPage = null;
    
    for (const page of pages) {
        for (const block of page.blocks) {
            if (block.getAddress() === address) {
                targetBlock = block;
                targetPage = page;
                break;
            }
        }
        if (targetBlock) break;
    }
    
    if (!targetBlock) {
        showMessage('Invalid pointer address', 'error');
        return;
    }
    
    if (targetBlock.isFree) {
        showMessage('Block already freed', 'error');
        return;
    }
    
    // Mark as free
    targetBlock.isFree = true;
    
    // Add to free list
    addToFreeList(targetBlock);
    
    // Update page used space
    targetPage.usedSpace -= (targetBlock.size + HEADER_SIZE);
    
    // Coalesce adjacent free blocks
    coalesceBlocks();
    
    renderMemory();
    updateStats();
    showFreeListInfo(); // Show free list info after each operation
    
    showMessage(`Freed block at address ${address}`, 'success');
}

// Realloc implementation
function realloc(ptr, newSize) {
    if (!ptr) {
        // realloc(NULL, size) is equivalent to malloc(size)
        return malloc(newSize);
    }
    
    const address = parseInt(ptr);
    if (isNaN(address)) {
        showMessage('Invalid pointer address', 'error');
        return null;
    }
    
    // Find block by address
    let targetBlock = null;
    let targetPage = null;
    
    for (const page of pages) {
        for (const block of page.blocks) {
            if (block.getAddress() === address) {
                targetBlock = block;
                targetPage = page;
                break;
            }
        }
        if (targetBlock) break;
    }
    
    if (!targetBlock) {
        showMessage('Invalid pointer address', 'error');
        return null;
    }
    
    // Add header size
    newSize += HEADER_SIZE;
    newSize = Math.max(newSize, MIN_BLOCK_SIZE);
    
    if (newSize > PAGE_SIZE) {
        showMessage(`Cannot allocate ${newSize} bytes - larger than page size`, 'error');
        return null;
    }
    
    // If new size is smaller, we might just leave it (simplified)
    if (newSize <= targetBlock.size) {
        // In a real implementation, we might split the block
        renderMemory();
        updateStats();
        showFreeListInfo(); // Show free list info after each operation
        return ptr;
    }
    
    // If new size is larger, we need to allocate a new block
    const newPtr = malloc(newSize - HEADER_SIZE);
    if (!newPtr) {
        return null;
    }
    
    // In a real implementation, we'd copy data here
    // For demo, we'll just free the old block
    free(ptr);
    
    renderMemory();
    updateStats();
    showFreeListInfo(); // Show free list info after each operation
    
    return newPtr;
}

// Event handlers
function handleMalloc() {
    const sizeInput = document.getElementById('malloc-size');
    const size = parseInt(sizeInput.value);
    
    if (isNaN(size) || size <= 0) {
        showMessage('Please enter a valid size', 'error');
        return;
    }
    
    const ptr = malloc(size);
    if (ptr) {
        showMessage(`Allocated ${size} bytes at address ${ptr}`, 'success');
    }
    
    sizeInput.value = '';
}

function handleFree() {
    const ptrInput = document.getElementById('free-ptr');
    const ptr = ptrInput.value.trim();
    
    if (!ptr) {
        showMessage('Please enter a pointer address', 'error');
        return;
    }
    
    free(ptr);
    ptrInput.value = '';
}

function handleRealloc() {
    const ptrInput = document.getElementById('realloc-ptr');
    const sizeInput = document.getElementById('realloc-size');
    const ptr = ptrInput.value.trim();
    const size = parseInt(sizeInput.value);
    
    if (!ptr) {
        showMessage('Please enter a pointer address', 'error');
        return;
    }
    
    if (isNaN(size) || size <= 0) {
        showMessage('Please enter a valid size', 'error');
        return;
    }
    
    const newPtr = realloc(ptr, size);
    if (newPtr && newPtr !== ptr) {
        showMessage(`Reallocated from address ${ptr} to address ${newPtr}`, 'success');
    }
    
    ptrInput.value = '';
    sizeInput.value = '';
}

// Function to show free list information
function showFreeListInfo() {
    let message = 'Free List Head: ';
    
    if (freeList === null) {
        message += 'NULL';
    } else {
        message += `Addr ${freeList.getAddress()} (${freeList.size} bytes) → `;
        
        let current = freeList;
        const addresses = [];
        
        while (current) {
            addresses.push(`Addr ${current.getAddress()} (${current.size} bytes)`);
            current = current.next;
        }
        
        message += addresses.join(' → ');
    }
    
    showMessage(message, 'success');
}

function resetAllocator() {
    pages = [];
    freeList = null;
    nextPageId = 0;
    nextBlockId = 0;
    
    // Reset to empty state (no pages allocated initially)
    renderMemory();
    updateStats();
    showFreeListInfo(); // Show free list info after reset
    showMessage('Allocator reset', 'success');
}

// Draw visualization of the free list structure
function drawFreeListVisualization() {
    const svg = document.getElementById('free-list-svg');
    const svgNS = "http://www.w3.org/2000/svg";
    
    // Clear existing visualization
    svg.innerHTML = '<defs><marker id="fl-arrowhead" markerWidth="10" markerHeight="7" refX="10" refY="3.5" orient="auto"><polygon points="0 0, 10 3.5, 0 7" fill="#FF6B6B"/></marker></defs>';
    
    // Start position
    let x = 50;
    const y = 50;
    
    // Draw "Free list" label
    const label = document.createElementNS(svgNS, 'text');
    label.setAttribute('x', x);
    label.setAttribute('y', y - 20);
    label.setAttribute('font-family', 'Arial');
    label.setAttribute('font-size', '16');
    label.setAttribute('fill', '#000');
    label.textContent = 'Free list:';
    svg.appendChild(label);
    
    // Draw arrow from "Free list" to first node or NULL
    const arrowStartX = x + 70;
    
    if (!freeList) {
        // Draw NULL
        const nullText = document.createElementNS(svgNS, 'text');
        nullText.setAttribute('x', arrowStartX + 20);
        nullText.setAttribute('y', y + 5);
        nullText.setAttribute('font-family', 'Arial');
        nullText.setAttribute('font-size', '16');
        nullText.setAttribute('fill', '#FF6B6B');
        nullText.textContent = 'NULL';
        svg.appendChild(nullText);
        
        // Draw arrow to NULL
        const line = document.createElementNS(svgNS, 'line');
        line.setAttribute('x1', arrowStartX);
        line.setAttribute('y1', y);
        line.setAttribute('x2', arrowStartX + 15);
        line.setAttribute('y2', y);
        line.setAttribute('stroke', '#FF6B6B');
        line.setAttribute('stroke-width', '2');
        line.setAttribute('marker-end', 'url(#fl-arrowhead)');
        svg.appendChild(line);
    } else {
        // Draw arrow to first node
        const line = document.createElementNS(svgNS, 'line');
        line.setAttribute('x1', arrowStartX);
        line.setAttribute('y1', y);
        line.setAttribute('x2', arrowStartX + 15);
        line.setAttribute('y2', y);
        line.setAttribute('stroke', '#FF6B6B');
        line.setAttribute('stroke-width', '2');
        line.setAttribute('marker-end', 'url(#fl-arrowhead)');
        svg.appendChild(line);
        
        // Draw free list nodes
        let current = freeList;
        x = arrowStartX + 30;
        
        while (current) {
            // Draw rectangle for node
            const rect = document.createElementNS(svgNS, 'rect');
            rect.setAttribute('x', x);
            rect.setAttribute('y', y - 15);
            rect.setAttribute('width', 180);
            rect.setAttribute('height', 30);
            rect.setAttribute('fill', '#4ECDC4');
            rect.setAttribute('stroke', '#333');
            rect.setAttribute('stroke-width', '1');
            rect.setAttribute('rx', '5'); // Rounded corners
            svg.appendChild(rect);
            
            // Draw text for node
            const text = document.createElementNS(svgNS, 'text');
            text.setAttribute('x', x + 90);
            text.setAttribute('y', y + 5);
            text.setAttribute('font-family', 'Arial');
            text.setAttribute('font-size', '12');
            text.setAttribute('fill', '#000');
            text.setAttribute('text-anchor', 'middle');
            text.textContent = `Addr ${current.getAddress()} (${current.size} bytes)`;
            svg.appendChild(text);
            
            // Draw arrow to next node or NULL
            if (current.next) {
                // Arrow to next node
                const arrowLine = document.createElementNS(svgNS, 'line');
                arrowLine.setAttribute('x1', x + 180);
                arrowLine.setAttribute('y1', y);
                arrowLine.setAttribute('x2', x + 210);
                arrowLine.setAttribute('y2', y);
                arrowLine.setAttribute('stroke', '#FF6B6B');
                arrowLine.setAttribute('stroke-width', '2');
                arrowLine.setAttribute('marker-end', 'url(#fl-arrowhead)');
                svg.appendChild(arrowLine);
                x += 210;
            } else {
                // Arrow to NULL
                const nullText = document.createElementNS(svgNS, 'text');
                nullText.setAttribute('x', x + 190);
                nullText.setAttribute('y', y + 5);
                nullText.setAttribute('font-family', 'Arial');
                nullText.setAttribute('font-size', '16');
                nullText.setAttribute('fill', '#FF6B6B');
                nullText.textContent = 'NULL';
                svg.appendChild(nullText);
                
                const arrowLine = document.createElementNS(svgNS, 'line');
                arrowLine.setAttribute('x1', x + 180);
                arrowLine.setAttribute('y1', y);
                arrowLine.setAttribute('x2', x + 190);
                arrowLine.setAttribute('y2', y);
                arrowLine.setAttribute('stroke', '#FF6B6B');
                arrowLine.setAttribute('stroke-width', '2');
                arrowLine.setAttribute('marker-end', 'url(#fl-arrowhead)');
                svg.appendChild(arrowLine);
            }
            
            current = current.next;
        }
    }
}

// Draw arrows to visualize the free list
function showMessage(text, type) {
    const messageArea = document.getElementById('message-area');
    messageArea.textContent = text;
    messageArea.className = type;
}

// Rendering functions
function renderMemory() {
    const container = document.getElementById('memory-container');
    container.innerHTML = '';
    
    // Clear memory arrows
    const svg = document.getElementById('arrows-svg');
    svg.innerHTML = '<defs><marker id="arrowhead" markerWidth="10" markerHeight="7" refX="10" refY="3.5" orient="auto"><polygon points="0 0, 10 3.5, 0 7" fill="#333"/></marker></defs>';
    
    // Render each page
    pages.forEach((page, pageIndex) => {
        const pageContainer = document.createElement('div');
        pageContainer.className = 'page-container';
        
        const pageElement = document.createElement('div');
        pageElement.className = 'page';
        pageElement.id = page.elementId;
        
        const pageHeader = document.createElement('div');
        pageHeader.className = 'page-header';
        pageHeader.textContent = `Page ${page.id}`;
        pageElement.appendChild(pageHeader);
        
        // Render each block in the page
        let yOffset = 40; // Start below page header
        page.blocks.forEach(block => {
            const blockElement = document.createElement('div');
            blockElement.className = 'block';
            blockElement.id = block.elementId;
            
            // Set dimensions and position
            const height = Math.max(30, Math.min(200, block.size / 20)); // Scale height
            blockElement.style.width = '280px';
            blockElement.style.height = `${height}px`;
            blockElement.style.top = `${yOffset}px`;
            blockElement.style.left = '10px';
            
            // Set color based on block type
            if (block.isFree) {
                blockElement.className += ' free';
            } else {
                blockElement.className += ' allocated';
            }
            
            // Add label
            const label = document.createElement('div');
            label.style.textAlign = 'center';
            const address = block.getAddress();
            label.innerHTML = `
                ${block.isFree ? 'FREE' : 'ALLOCATED'}<br/>
                ${block.size} bytes<br/>
                Addr: ${address}
            `;
            blockElement.appendChild(label);
            
            // Add click handler for allocated blocks
            if (!block.isFree) {
                blockElement.style.cursor = 'pointer';
                blockElement.addEventListener('click', function() {
                    // Fill in the actual address in both input boxes
                    document.getElementById('free-ptr').value = address;
                    document.getElementById('realloc-ptr').value = address;
                    
                    // Show a message
                    showMessage(`Selected block at address ${address} for free/realloc operations`, 'success');
                });
            }
            
            pageElement.appendChild(blockElement);
            yOffset += height + 5; // Add spacing
        });
        
        pageContainer.appendChild(pageElement);
        container.appendChild(pageContainer);
    });
    
    // Draw free list visualization
    setTimeout(drawFreeListVisualization, 50);
}

function drawFreeListArrows() {
    // Clear any existing timeout
    if (window.drawFreeListTimeout) {
        clearTimeout(window.drawFreeListTimeout);
        window.drawFreeListTimeout = null;
    }
    
    const svg = document.getElementById('arrows-svg');
    const svgNS = "http://www.w3.org/2000/svg";
    
    // Clear existing arrows except defs
    while (svg.childNodes.length > 1) {
        svg.removeChild(svg.lastChild);
    }
    
    // Draw arrows for free list
    let current = freeList;
    let positions = [];
    
    // First, collect all positions
    while (current) {
        const blockElement = document.getElementById(current.elementId);
        if (blockElement) {
            const rect = blockElement.getBoundingClientRect();
            const containerRect = svg.getBoundingClientRect();
            
            const x = rect.left - containerRect.left + rect.width / 2;
            const y = rect.top - containerRect.top + rect.height / 2;
            
            positions.push({x, y, block: current});
        }
        current = current.next;
    }
    
    // Then draw arrows between consecutive positions
    for (let i = 0; i < positions.length - 1; i++) {
        const start = positions[i];
        const end = positions[i + 1];
        
        // Draw circle at block
        const circle = document.createElementNS(svgNS, 'circle');
        circle.setAttribute('cx', start.x);
        circle.setAttribute('cy', start.y);
        circle.setAttribute('r', 5);
        circle.setAttribute('fill', '#FF6B6B');
        svg.appendChild(circle);
        
        // Draw arrow from current to next
        const line = document.createElementNS(svgNS, 'line');
        line.setAttribute('x1', start.x);
        line.setAttribute('y1', start.y);
        line.setAttribute('x2', end.x);
        line.setAttribute('y2', end.y);
        line.className = 'arrow free-list-line';
        svg.appendChild(line);
    }
    
    // Draw circle for last element
    if (positions.length > 0) {
        const last = positions[positions.length - 1];
        const circle = document.createElementNS(svgNS, 'circle');
        circle.setAttribute('cx', last.x);
        circle.setAttribute('cy', last.y);
        circle.setAttribute('r', 5);
        circle.setAttribute('fill', '#FF6B6B');
        svg.appendChild(circle);
    }
}

function updateStats() {
    let totalMemory = 0;
    let allocatedMemory = 0;
    let freeMemory = 0;
    
    pages.forEach(page => {
        totalMemory += PAGE_SIZE;
        page.blocks.forEach(block => {
            if (block.isFree) {
                freeMemory += block.size;
            } else {
                allocatedMemory += block.size;
            }
        });
    });
    
    // Update stats display
    document.getElementById('total-memory').textContent = totalMemory;
    document.getElementById('allocated-memory').textContent = allocatedMemory;
    document.getElementById('free-memory').textContent = freeMemory;
    
    // Calculate fragmentation (simplified)
    const fragmentation = totalMemory > 0 ? 
        Math.round(((totalMemory - freeMemory - allocatedMemory) / totalMemory) * 100) : 0;
    document.getElementById('fragmentation').textContent = fragmentation;
}

// Initialize when script loads
if (document.readyState === 'loading') {
    document.addEventListener('DOMContentLoaded', initAllocator);
} else {
    initAllocator();
}